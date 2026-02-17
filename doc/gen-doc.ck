CKDoc doc;
"../examples/" => doc.examplesRoot;

doc.addGroup(
    ["EncodeN", "BAFormat", "ABFormat"],
    "Ambisonic Encoders & Converters",
    "encoders",
    "Virtual source Encoders and file type coverters for A to B and B to A format conversions."
);

doc.addGroup(
    ["DecodeN", "DBDN", "SADN"],
    "Ambisonic Decoders",
    "decoders",
    "Ambisonic decoders operating from 1st to 5th order."
);

doc.outputToDir(".", "Chumbi API Reference");