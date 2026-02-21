#!/bin/bash

if [ $# -eq 0 ]; then
    echo "input arguments [ os ] include mac, linux, win32"
    exit 1
fi

OS="$1"
VERS="1.1.0"
BUILD_DIR="current-builds"
ROOT_DIR="$(pwd)"
DEST_DIR="$ROOT_DIR/$BUILD_DIR"
# collection of source paths and output files
CHUGS=(
    "B-A-BFormat.chug/ABFormat.chug:ABFormat.chug"
    "B-A-BFormat.chug/BAFormat.chug:BAFormat.chug"
    "Encode.chug/:Encode.chug"
    "Decode.chug/DecodeN:Decode.chug"
    "Decode.chug/SADN:SADN.chug"
    "OrderGain.chug/:OrderGain.chug"
    "Mirror.chug:Mirror.chug"
)
# build function
build_and_move() {
    local path="$1"
    local chug="$2"
    
    echo "Building $chug"
    
    cd "$path" || { echo "Failed to enter $path"; exit 1; }
    make clean
    make "$OS"
    
    if [[ "$OS" == "win32" ]]; then
        cp "x64/Release/$chug" "$DEST_DIR/win/"
    else
        cp "$chug" "$DEST_DIR/$OS/"
    fi
    
    cd "$ROOT_DIR" || exit 1
}

# make dir if it doesn't exist
if [[ "$OS" == "win32" ]]; then
    mkdir -p "$BUILD_DIR/win/"
else
    mkdir -p "$BUILD_DIR"
fi

# build away
for entry in "${CHUGS[@]}"; do
    IFS=':' read -r path chug <<< "$entry"
    build_and_move "$path" "$chug"
done

echo "All builds completed successfully"
if [[ "$OS" == "win32" ]]; then
    ls --time=creation -l $BUILD_DIR/win/
    zip $BUILD_DIR/win/ chumbi-win
    zip -r -b $BUILD_DIR/win/ chumbi-win-v$VERS.zip $BUILD_DIR/win/
else 
    ls --time=creation -l $BUILD_DIR/$OS
    zip -r -b $BUILD_DIR/ chumbi-$OS-v$VERS.zip $BUILD_DIR/$OS/
fi