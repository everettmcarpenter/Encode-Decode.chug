//---------------------------------------------------------------------
// author: everett m. carpenter (but heavily taken from Ge Wang & Nick Shaheed)
//---------------------------------------------------------------------

CKDoc doc;

// encoders
doc.addGroup(
    ["EncodeN", "ABFormat", "BAFormat"],
    "Encoders and Converters",
    "encoders", 
    "Ambisonic virtual encoders and microphone utilities. Encoder works from 1st to 5th order."
);

// decoders
doc.addGroup(
    [ "DecodeN", "MonoDecodeN", "SADN", "DBDN"],
    "Decoders",
    "decoders",
    "Ambisonic decoders, all work from 1st to 5th order."
);

//utilities
doc.addGroup(
    [ "OrderGainN", "MirrorN", "RotateN", "WarpN" ],
    "Soundfield Utilities",
    "utilities",
    "Basic soundfield alterers, shapers and modifiers, all work from 1st to 5th order."
);


doc.genGroups(["Encoders and Converters", "Decoders", "Soundfield Utilities"]);

// generate
doc.outputToDir( "chumbi-doc/", "Chumbi Doc" );
