let greyscale = true;

let binary = false;
let boundery = 0;

let colour = false;

let boundery1 = document.getElementById("b1").value;
let boundery2 = document.getElementById("b2").value;
let boundery3 = document.getElementById("b3").value;
let boundery4 = document.getElementById("b4").value;
let boundery5 = document.getElementById("b5").value;
let boundery6 = document.getElementById("b6").value;
let boundery7 = document.getElementById("b7").value;
let boundery8 = document.getElementById("b8").value;

let Seed = 0;
let ChunkLength = 0;
let SideLength = 0;
let Lactunarity = 0;
let Persistance = 0;
let Octaves = 0;
let ChunksInSide = 0;

const maxSeed = 2**32;
const Canvas = document.getElementById("canvas");

let Values = [];
let Permutations = [];


const rangeInput = document.getElementById("boundery");
const display = document.getElementById("displayBoundery");

rangeInput.addEventListener("input", function(){
    boundery = rangeInput.value;
    display.innerHTML = "boundery is " + String(boundery);
});

function hexToRgb(hex) {
    hex = hex.replace(/^#/, '');
    return [
        parseInt(hex.substring(0, 2), 16),
        parseInt(hex.substring(2, 4), 16),
        parseInt(hex.substring(4, 6), 16)
    ];
}
function getBounderies(){
    boundery1 = hexToRgb(document.getElementById("b1").value);
    boundery2 = hexToRgb(document.getElementById("b2").value);
    boundery3 = hexToRgb(document.getElementById("b3").value);
    boundery4 = hexToRgb(document.getElementById("b4").value);
    boundery5 = hexToRgb(document.getElementById("b5").value);
    boundery6 = hexToRgb(document.getElementById("b6").value);
    boundery7 = hexToRgb(document.getElementById("b7").value);
    boundery8 = hexToRgb(document.getElementById("b8").value);
}


function activeGreyscale(){
    greyscale = true;
    binary = false;
    colour = false;}

function activeBinary(){
    greyscale = false;
    binary = true;
    colour = false;}

function activeColour(){
    greyscale = false;
    binary = false;
    colour = true;}

function randomiseSeed()
{
    newSeed = Math.floor(Math.random() * ((maxSeed) - 1));
    document.getElementById("seed").value = String(newSeed);
    return;
}

function inputValidity(seed, chunkLength, sideLength, lactunarity, persistance, octaves)
{
    // SEED validation
    if (seed >= maxSeed || seed < 0) {return ["ERROR: Seed parameter is currently not between 0 and 4294967295 (2^32), MUST an integer value within this range", false];}
    else if (! Number.isInteger(seed)){return ["ERROR: Seed parameter is currently a float, MUST be an integer value", false];}
    // CHUNKLENGTH & SIDELENGTH validation
    else if ((! Number.isInteger(chunkLength)) || (! Number.isInteger(sideLength))){return ["ERROR: Chunk side-length or map side-length is currently a float, MUST both be an integer value", false];}
    else if (chunkLength < 3 || sideLength < 3){return ["ERROR: Chunk side-length or map side-length is currently lower than 3, MUST be a integer value larger than or equal to 3", false];}
    else if(! Number.isInteger(sideLength / (chunkLength * (lactunarity ** (octaves-1))))){return ["ERROR: The chunks side-length does not fit within the maps side-length an integer number of times for one or more octaves, MUST fit within the maps side length an integer number of times for all octaves", false];}
    // LACTUNARITY validation
    else if (lactunarity < 0){return ["ERROR: Lactunarity parameter is currently lower than 0, MUST be a numeric value larger than or equal to 0", false];}
    // PERSISTANCE validation
    else if (persistance < 0){return ["ERROR: Persistance parameter is currently lower than 0, MUST be a numeric value larger than or equal to 0", false];}
    // Octave validation
    else if (octaves < 1){return ["ERROR: Octave parameter is currently lower than 1, MUST be a integer value larger than or equal to 1", false];}
    else if (! Number.isInteger(octaves)){return ["ERROR: Octave parameter is currently a float, MUST be an integer value", false];}
    // Its valid
    else {return ["Parameters function correctly together and independently!", true];}
}

function canProceed(seed, chunkLength, sideLength, lactunarity, persistance, octaves)
{
    let feedback = inputValidity(Number(seed), Number(chunkLength), Number(sideLength), Number(lactunarity), Number(persistance), Number(octaves));
    let element = document.getElementById("error")
    if (! feedback[1])
        {
            element.innerHTML = feedback[0];
            element.style.color = "red";
            return;
        }
    element.innerHTML = feedback[0]
    element.style.color = "green";

    Seed = seed;
    ChunkLength = chunkLength;
    SideLength = sideLength;
    Lactunarity = lactunarity;
    Persistance = persistance;
    Octaves = octaves;
    ChunksInSide = SideLength / ChunkLength;
    setCanvas();
}

function redefArrays() {
    Values = [];
    for (let i = 0; i < SideLength; i++) {
        Values[i] = [];
        for (let j = 0; j < SideLength; j++) {
            Values[i][j] = 0;
        }
    }

    Permutations = []
    for (let i = 0; i < ChunksInSide + 1; i++) {
        Permutations[i] = [];
        for (let j = 0; j < ChunksInSide + 1; j++) {
            Permutations[i][j] = 0;
        }
    }
}

function setCanvas()
{
    canvas.width = SideLength;
    canvas.height = SideLength;

    redefArrays();
    PerlinNoise(Values);

    let ctx = canvas.getContext("2d");
    let imageData = ctx.createImageData(canvas.width, canvas.height);
    let data = imageData.data;

    for (let y = 0; y < canvas.height; y++) {
        for (let x = 0; x < canvas.width; x++) {
            let i = (y * canvas.width + x) * 4;
            let translated = translatePixel(Values[x][y]);
            data[i] = translated[0];
            data[i+1] = translated[1];
            data[i+2] = translated[2];
            data[i+3] = 255;
        }
    }
    ctx.putImageData(imageData, 0, 0);
}

function translatePixel(value){
    if (greyscale){
        let calc = Math.round(((value+1)/2)*255);
        return [calc, calc, calc];
    }
    if (binary){
        if (value > boundery){return [255, 255, 255];}
        else{return [0, 0, 0];}
    }
    else{
        getBounderies();
        if (value > 0.74){return boundery1;}
        else if (value > 0.49){return boundery2;}
        else if (value > 0.24){return boundery3;}
        else if (value > -0.01){return boundery4;}
        else if (value > -0.26){return boundery5;}
        else if (value > -0.51){return boundery6;}
        else if (value > -0.76){return boundery7;}
        else {return boundery8;}
    }
}

function PerlinNoise(Values){
    let InputChunkLength = ChunkLength;

    let PRNG = new Math.seedrandom(Seed);
    for (let i = 0; i < Permutations.length; i++){
        for (let j = 0; j < Permutations[i].length; j++){
            Permutations[i][j] = Math.floor(PRNG() * 4);
        }
    }

    for (let Octave = 0; Octave < Octaves; Octave++)
    {
        let PixelsInChunk = InputChunkLength * (Lactunarity ** ((Octaves -1) - Octave))
        let ChunksInSide = SideLength / PixelsInChunk;
        let CurrentPersistence = Persistance ** Octave;
        console.log(CurrentPersistence);
        ChunkByChunk(PixelsInChunk, ChunksInSide, CurrentPersistence);
    }
}

function GetVector(value)
{
    switch (value){
        case 0:
            return [1, 1];
        case 1:
            return [-1, 1];
        case 2:
            return [1, -1];
        default:
            return [-1, -1];
    }
}

function ChunkByChunk(PixelsInChunk, ChunksInSide, Influence)
{
    for (let i = 0; i < ChunksInSide; i++){
        for (let j = 0; j < ChunksInSide; j++){
            let TopLeft = GetVector(Permutations[i][j]);
            let TopRight = GetVector(Permutations[i][j+1]);
            let BottomLeft = GetVector(Permutations[i+1][j]);
            let BottomRight = GetVector(Permutations[i+1][j+1]);
            CompleteChunk(PixelsInChunk, j, i, Influence, TopLeft, TopRight, BottomLeft, BottomRight);
        }
    }
}

function dot(vec1, vec2) {return (vec1[0] * vec2[0]) + (vec1[1] * vec2[1]);}
function fade(value){return ((6 * value - 15) * value + 10) * value * value * value;}
function lerp (per, var1, var2){return var1 + (per * (var2 - var1));}

function CompleteChunk(PixelsInChunk, XChunk, YChunk, Influence, TL, TR, BL, BR)
{
    for (let i = 0; i < PixelsInChunk; i++){
        let PercentY = (i+1) / PixelsInChunk;

        for (let j = 0; j < PixelsInChunk; j++){
            let PercentX = (j+1) / PixelsInChunk;

            let x = (YChunk * PixelsInChunk) + i;
            let y = (XChunk * PixelsInChunk) + j;

            let dotTL = dot(TL, [PercentX, PercentY]);
            let dotTR = dot(TR, [PercentX - 1, PercentY]);
            let dotBL = dot(BL, [PercentX, PercentY - 1]);
            let dotBR = dot(BR, [PercentX - 1, PercentY -1]);

            let u = 1 - fade(PercentX);
            let v = fade(PercentY);

            let value = lerp(v, lerp(u, dotTR, dotTL), lerp(u, dotBR, dotBL));

            Values[x][y] = Math.max(-1, Math.min(1, Values[x][y] + (value * Influence)));
        }
    }
}
