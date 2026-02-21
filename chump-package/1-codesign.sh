#--------------------------------------------------------------
# codesign.sh
# pre-condition: both arm64 and intel Chumpinate.chug builds
#  are located in the proper directories 
#--------------------------------------------------------------

# taken from Nick Shaheed (thanks dude)

# collection of source paths and output files
CHUGS=(
    "../current-builds/mac/ABFormat.chug"
    "../current-builds/mac/BAFormat.chug"
    "../current-builds/mac/Encode.chug"
    "../current-builds/mac/Decode.chug"
    "../current-builds/mac/SADN.chug"
    "../current-builds/mac/OrderGain.chug"
    "../current-builds/mac/Mirror.chug"
)

# where the Chumpinate build can be foundy
for entry in "${CHUGS[@]}"; do
    CHUG=$entry
    echo "codesigning" $entry
    # remove code signature from chugin and dylibs
    codesign --remove-signature ${CHUG}

    # codesign Chumpinate.chug
    codesign --deep --force --verify --verbose --timestamp --options runtime --entitlements Chumpinate.entitlements --sign "Developer ID Application" ${CHUG}
done