API REFERENCE:

https://everettmiles.com/chumbi-doc/

# Encode-Decode.chug
Ambisonic encoding and decoding chugins for ChucK

Currently functional:

      EncodeN // virtual source encoder & ambisonic panner
      SADN // sampling ambisonic decoder designed to receive speaker array angles
      DecodeN // sampling ambisonic decoder designed to receive speaker spherical harmonics
      DBDN // dual band ambisonic decoding
      BFormatN // gain UGen for BFormat signals (multi channel gain factor)
      ABFormat // convert AFormat to BFormat
      BAFormat // convert BFormat to AFormat
      MirrorN // mirroring of sound fields along axes

Coming soon:

      MMADN // mode matching ambisonic decoding
      RotateN // rotation of sound fields
      WarpN // warping of sound fields

All UGens are capable of up to 5th order ambisonics, but can be compiled to 12th order if desired.
