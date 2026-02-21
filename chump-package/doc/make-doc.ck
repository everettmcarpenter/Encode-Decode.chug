//---------------------------------------------------------------------
// author: everett m. carpenter (but heavily taken from Ge Wang & Nick Shaheed)
//---------------------------------------------------------------------

CKDoc doc;

// encoders
doc.addGroup(
    ["Encode1", "ABFormat", "BAFormat"],
    "Encoders and Converters",
    "encoders", 
    "Ambisonic virtual encoders and microphone utilities. Encoder works from 1st to 5th order."
);

// decoders
doc.addGroup(
    [ "Decode1", "SAD1", "DBD1"],
    "Decoders",
    "decoders",
    "Ambisonic decoders, all work from 1st to 5th order."
);

//utilities
doc.addGroup(
    [ "OrderGain1", "Mirror1", "Rotate1", "Warp1" ],
    "Soundfield Utilities",
    "utilities",
    "Basic soundfield alterers, shapers and modifiers, all work from 1st to 5th order."
);


doc.genGroups(["Encoders and Converters", "Decoders", "Soundfield Utilities"]);

// generate
doc.outputToDir( ".", "Chumbi Doc" );
