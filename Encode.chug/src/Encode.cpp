//-----------------------------------------------------------------------------
// Author: Everett M. Carpenter
// Date: Summer 2025
//-----------------------------------------------------------------------------
// happy chucking & chugging!
//-----------------------------------------------------------------------------

// include chugin header
#include "chugin.h"

// general includes
#include <stdio.h>
#include <limits.h>
#include <math.h>
#include "chuckSH.h"
#include "Encode.h"

// declaration of chugin constructor
// Encode1
CK_DLL_CTOR(encode1_ctor);
CK_DLL_DTOR(encode1_dtor);
CK_DLL_TICKF(encode1_tickf);
CK_DLL_MFUN(encode1_geti);
CK_DLL_MFUN(encode1_seti);
CK_DLL_MFUN(encode1_coefficients);
CK_DLL_MFUN(encode1_position);
CK_DLL_MFUN(encode1_getSH);
CK_DLL_MFUN(encode1_setWeights);
CK_DLL_MFUN(encode1_getWeights);
CK_DLL_MFUN(encode1_getAzi);
CK_DLL_MFUN(encode1_getZeni);
CK_DLL_MFUN(encode1_setAzi);
CK_DLL_MFUN(encode1_setZeni);
t_CKINT encode1_data_offset = 0;
// Encode2
CK_DLL_CTOR(encode2_ctor);
CK_DLL_DTOR(encode2_dtor);
CK_DLL_TICKF(encode2_tickf);
CK_DLL_MFUN(encode2_geti);
CK_DLL_MFUN(encode2_seti);
CK_DLL_MFUN(encode2_coefficients);
CK_DLL_MFUN(encode2_position);
CK_DLL_MFUN(encode2_getSH);
CK_DLL_MFUN(encode2_setWeights);
CK_DLL_MFUN(encode2_getWeights);
CK_DLL_MFUN(encode2_getAzi);
CK_DLL_MFUN(encode2_getZeni);
CK_DLL_MFUN(encode2_setAzi);
CK_DLL_MFUN(encode2_setZeni);
t_CKINT encode2_data_offset = 0;
// Encode3
CK_DLL_CTOR(encode3_ctor);
CK_DLL_DTOR(encode3_dtor);
CK_DLL_TICKF(encode3_tickf);
CK_DLL_MFUN(encode3_geti);
CK_DLL_MFUN(encode3_seti);
CK_DLL_MFUN(encode3_coefficients);
CK_DLL_MFUN(encode3_position);
CK_DLL_MFUN(encode3_getSH);
CK_DLL_MFUN(encode3_setWeights);
CK_DLL_MFUN(encode3_getWeights);
CK_DLL_MFUN(encode3_getAzi);
CK_DLL_MFUN(encode3_getZeni);
CK_DLL_MFUN(encode3_setAzi);
CK_DLL_MFUN(encode3_setZeni);
t_CKINT encode3_data_offset = 0;
// Encode4
CK_DLL_CTOR(encode4_ctor);
CK_DLL_DTOR(encode4_dtor);
CK_DLL_TICKF(encode4_tickf);
CK_DLL_MFUN(encode4_geti);
CK_DLL_MFUN(encode4_seti);
CK_DLL_MFUN(encode4_coefficients);
CK_DLL_MFUN(encode4_position);
CK_DLL_MFUN(encode4_getSH);
CK_DLL_MFUN(encode4_setWeights);
CK_DLL_MFUN(encode4_getWeights);
CK_DLL_MFUN(encode4_getAzi);
CK_DLL_MFUN(encode4_getZeni);
CK_DLL_MFUN(encode4_setAzi);
CK_DLL_MFUN(encode4_setZeni);
t_CKINT encode4_data_offset = 0;
// Encode5
CK_DLL_CTOR(encode5_ctor);
CK_DLL_DTOR(encode5_dtor);
CK_DLL_TICKF(encode5_tickf);
CK_DLL_MFUN(encode5_geti);
CK_DLL_MFUN(encode5_seti);
CK_DLL_MFUN(encode5_coefficients);
CK_DLL_MFUN(encode5_position);
CK_DLL_MFUN(encode5_getSH);
CK_DLL_MFUN(encode5_setWeights);
CK_DLL_MFUN(encode5_getWeights);
CK_DLL_MFUN(encode5_getAzi);
CK_DLL_MFUN(encode5_getZeni);
CK_DLL_MFUN(encode5_setAzi);
CK_DLL_MFUN(encode5_setZeni);
t_CKINT encode5_data_offset = 0;

//-----------------------------------------------------------------------------
// info function: ChucK calls this when loading/probing the chugin
// NOTE: please customize these info fields below; they will be used for
// chugins loading, probing, and package management and documentation
//-----------------------------------------------------------------------------
CK_DLL_INFO(Encode)
{
    // the version string of this chugin, e.g., "v1.2.1"
    QUERY->setinfo(QUERY, CHUGIN_INFO_CHUGIN_VERSION, "v1.0.0");
    // the author(s) of this chugin, e.g., "Alice Baker & Carl Donut"
    QUERY->setinfo(QUERY, CHUGIN_INFO_AUTHORS, "Everett M. Carpenter");
    // text description of this chugin; what is it? what does it do? who is it for?
    QUERY->setinfo(QUERY, CHUGIN_INFO_DESCRIPTION, "First through fifth Ambisonic encoding within ChucK");
    // (optional) URL of the homepage for this chugin
    QUERY->setinfo(QUERY, CHUGIN_INFO_URL, "https://github.com/SaintEverett/Encode-Decode.chug/tree/32486a2a3fcbb03b66f6b0c5dfaeed064a58e200/Encode.chug");
    // (optional) contact email
    QUERY->setinfo(QUERY, CHUGIN_INFO_EMAIL, "carpee2[at]rpi[dot]edu");
}

//-----------------------------------------------------------------------------
// query function: ChucK calls this when loading the chugin
// modify this function to define this chugin's API and language extensions
//-----------------------------------------------------------------------------
CK_DLL_QUERY(Encode)
{
    // generally, don't change this...
    QUERY->setname(QUERY, "Encode");

    // ------------------------------------------------------------------------
    // begin class definition(s) Encode1; will be compiled, verified,
    // and added to the chuck host type system for use
    // ------------------------------------------------------------------------
    // NOTE to create a non-UGen class, change the second argument
    // to extend a different ChucK class (e.g., "Object")
    QUERY->begin_class(QUERY, "Encode1", "UGen");
    QUERY->doc_class(QUERY, "A first order ambisonic virtual source encoder.");
    // register the destructor (probably no need to change)
    QUERY->add_ctor(QUERY, encode1_ctor);
    QUERY->add_dtor(QUERY, encode1_dtor);
    QUERY->add_ugen_funcf(QUERY, encode1_tickf, NULL, 1, 4);
    // get SH
    QUERY->add_mfun(QUERY, encode1_geti, "float", "sh");
    QUERY->add_arg(QUERY, "int", "n");
    QUERY->doc_func(QUERY, "Get nth spherical harmonic currently being used.");
    // set all SHs
    QUERY->add_mfun(QUERY, encode1_coefficients, "void", "sh");
    QUERY->add_arg(QUERY, "float[]", "coordinates");
    QUERY->doc_func(QUERY, "Set 1D array of all spherical harmonics currently being used.");
    // set SH
    QUERY->add_mfun(QUERY, encode1_seti, "void", "sh");
    QUERY->add_arg(QUERY, "float", "value");
    QUERY->add_arg(QUERY, "int", "n");
    QUERY->doc_func(QUERY, "Set nth spherical harmonic to be used.");
    // position source within this chugin (easier)
    QUERY->add_mfun(QUERY, encode1_position, "void", "pos");
    QUERY->add_arg(QUERY, "float", "azimuth");
    QUERY->add_arg(QUERY, "float", "zenith");
    QUERY->doc_func(QUERY, "Set azimuth and zenith of encoder virtual source.");
    // retrieve SH
    QUERY->add_mfun(QUERY, encode1_getSH, "float[]", "sh");
    QUERY->doc_func(QUERY, "Get 1D array of all spherical harmonics currently being used.");
    // retrieve last azimuth 
    QUERY->add_mfun(QUERY, encode1_getAzi, "float", "azi");
    QUERY->doc_func(QUERY, "Get last given azimuth.");
    // retrieve last given zenith
    QUERY->add_mfun(QUERY, encode1_getZeni, "float", "zeni");
    QUERY->doc_func(QUERY, "Get last given zenith.");
    // set azimuth 
    QUERY->add_mfun(QUERY, encode1_setAzi, "float", "azi");
    QUERY->add_arg(QUERY, "float", "azimuth");
    QUERY->doc_func(QUERY, "Set azimuth.");
    // set  zenith
    QUERY->add_mfun(QUERY, encode1_setZeni, "float", "zeni");
    QUERY->add_arg(QUERY, "float", "zenith");
    QUERY->doc_func(QUERY, "Set zenith.");
    // set weights
    QUERY->add_mfun(QUERY, encode1_setWeights, "void", "weights");
    QUERY->add_arg(QUERY, "float[]", "weights");
    QUERY->doc_func(QUERY,"Set 1D array of weighting for all spherical harmonics.");
    QUERY->add_mfun(QUERY, encode1_getWeights, "float[]", "weights");
    QUERY->doc_func(QUERY,"Get 1D array of weighting for all spherical harmonics.");
    // this reserves a variable in the ChucK internal class to store
    // referene to the c++ class we defined above
    encode1_data_offset = QUERY->add_mvar(QUERY, "int", "@e_data", false);
    QUERY->end_class(QUERY);

    // ------------------------------------------------------------------------
    // begin class definition(s) Encode2; will be compiled, verified,
    // and added to the chuck host type system for use
    // ------------------------------------------------------------------------
    // NOTE to create a non-UGen class, change the second argument
    // to extend a different ChucK class (e.g., "Object")
    QUERY->begin_class(QUERY, "Encode2", "UGen");
    QUERY->doc_class(QUERY, "A second order ambisonic virtual source encoder.");
    // register the destructor (probably no need to change)
    QUERY->add_ctor(QUERY, encode2_ctor);
    QUERY->add_dtor(QUERY, encode2_dtor);
    QUERY->add_ugen_funcf(QUERY, encode2_tickf, NULL, 1, 9);
    QUERY->add_mfun(QUERY, encode2_geti, "float", "sh");
    QUERY->add_arg(QUERY, "int", "n");
    QUERY->doc_func(QUERY, "Get nth spherical harmonic currently being used.");
    QUERY->add_mfun(QUERY, encode2_coefficients, "void", "sh");
    QUERY->add_arg(QUERY, "float[]", "coordinates");
    QUERY->doc_func(QUERY, "Set 1D array of all spherical harmonics currently being used.");
    QUERY->add_mfun(QUERY, encode2_seti, "void", "sh");
    QUERY->add_arg(QUERY, "float", "value");
    QUERY->add_arg(QUERY, "int", "n");
    QUERY->doc_func(QUERY, "Set nth spherical harmonic to be used.");
    QUERY->add_mfun(QUERY, encode2_position, "void", "pos");
    QUERY->add_arg(QUERY, "float", "azimuth");
    QUERY->add_arg(QUERY, "float", "zenith");
    QUERY->add_mfun(QUERY, encode2_getSH, "float[]", "sh");
    QUERY->doc_func(QUERY, "Get 1D array of all spherical harmonics currently being used.");
    QUERY->add_mfun(QUERY, encode2_getAzi, "float", "azi");
    QUERY->doc_func(QUERY, "Get last given azimuth.");
    QUERY->add_mfun(QUERY, encode2_getZeni, "float", "zeni");
    QUERY->doc_func(QUERY, "Get last given zenith.");
    QUERY->add_mfun(QUERY, encode2_setAzi, "float", "azi");
    QUERY->add_arg(QUERY, "float", "azimuth");
    QUERY->doc_func(QUERY, "Set azimuth.");
    QUERY->add_mfun(QUERY, encode2_setZeni, "float", "zeni");
    QUERY->add_arg(QUERY, "float", "zenith");
    QUERY->doc_func(QUERY, "Set zenith.");
    QUERY->add_mfun(QUERY, encode2_setWeights, "void", "weights");
    QUERY->add_arg(QUERY, "float[]", "weights");
    QUERY->doc_func(QUERY,"Set 1D array of weighting for all spherical harmonics.");
    QUERY->add_mfun(QUERY, encode2_getWeights, "float[]", "weights");
    QUERY->doc_func(QUERY,"Get 1D array of weighting for all spherical harmonics.");
    // this reserves a variable in the ChucK internal class to store
    // referene to the c++ class we defined above
    encode2_data_offset = QUERY->add_mvar(QUERY, "int", "@e_data", false);
    QUERY->end_class(QUERY);

    // ------------------------------------------------------------------------
    // begin class definition(s) Encode3; will be compiled, verified,
    // and added to the chuck host type system for use
    // ------------------------------------------------------------------------
    // NOTE to create a non-UGen class, change the second argument
    // to extend a different ChucK class (e.g., "Object")
    QUERY->begin_class(QUERY, "Encode3", "UGen");
    QUERY->doc_class(QUERY, "A third order ambisonic virtual source encoder.");
    // register the destructor (probably no need to change)
    QUERY->add_ctor(QUERY, encode3_ctor);
    QUERY->add_dtor(QUERY, encode3_dtor);
    QUERY->add_ugen_funcf(QUERY, encode3_tickf, NULL, 1, 16);
    QUERY->add_mfun(QUERY, encode3_geti, "float", "sh");
    QUERY->add_arg(QUERY, "int", "n");
    QUERY->doc_func(QUERY, "Get nth spherical harmonic currently being used.");
    QUERY->add_mfun(QUERY, encode3_coefficients, "void", "sh");
    QUERY->add_arg(QUERY, "float[]", "coordinates");
    QUERY->doc_func(QUERY, "Set 1D array of all spherical harmonics currently being used.");
    QUERY->add_mfun(QUERY, encode3_seti, "void", "sh");
    QUERY->add_arg(QUERY, "float", "value");
    QUERY->add_arg(QUERY, "int", "n");
    QUERY->doc_func(QUERY, "Set nth spherical harmonic to be used.");
    QUERY->add_mfun(QUERY, encode3_position, "void", "pos");
    QUERY->add_arg(QUERY, "float", "azimuth");
    QUERY->add_arg(QUERY, "float", "zenith");
    QUERY->add_mfun(QUERY, encode3_getSH, "float[]", "sh");
    QUERY->doc_func(QUERY, "Get 1D array of all spherical harmonics currently being used.");
    QUERY->add_mfun(QUERY, encode3_getAzi, "float", "azi");
    QUERY->doc_func(QUERY, "Get last given azimuth.");
    QUERY->add_mfun(QUERY, encode3_getZeni, "float", "zeni");
    QUERY->doc_func(QUERY, "Get last given zenith.");
    QUERY->add_mfun(QUERY, encode3_setAzi, "float", "azi");
    QUERY->add_arg(QUERY, "float", "azimuth");
    QUERY->doc_func(QUERY, "Set azimuth.");
    QUERY->add_mfun(QUERY, encode3_setZeni, "float", "zeni");
    QUERY->add_arg(QUERY, "float", "zenith");
    QUERY->doc_func(QUERY, "Set zenith.");
    QUERY->add_mfun(QUERY, encode3_setWeights, "void", "weights");
    QUERY->add_arg(QUERY, "float[]", "weights");
    QUERY->doc_func(QUERY,"Set 1D array of weighting for all spherical harmonics.");
    QUERY->add_mfun(QUERY, encode3_getWeights, "float[]", "weights");
    QUERY->doc_func(QUERY,"Get 1D array of weighting for all spherical harmonics.");
    // this reserves a variable in the ChucK internal class to store
    // referene to the c++ class we defined above
    encode3_data_offset = QUERY->add_mvar(QUERY, "int", "@e_data", false);
    QUERY->end_class(QUERY);

    // ------------------------------------------------------------------------
    // begin class definition(s) Encode4; will be compiled, verified,
    // and added to the chuck host type system for use
    // ------------------------------------------------------------------------
    // NOTE to create a non-UGen class, change the second argument
    // to extend a different ChucK class (e.g., "Object")
    QUERY->begin_class(QUERY, "Encode4", "UGen");
    QUERY->doc_class(QUERY, "A fourth order ambisonic virtual source encoder.");
    // register the destructor (probably no need to change)
    QUERY->add_ctor(QUERY, encode4_ctor);
    QUERY->add_dtor(QUERY, encode4_dtor);
    QUERY->add_ugen_funcf(QUERY, encode4_tickf, NULL, 1, 25);
    QUERY->add_mfun(QUERY, encode4_geti, "float", "sh");
    QUERY->add_arg(QUERY, "int", "n");
    QUERY->doc_func(QUERY, "Get nth spherical harmonic currently being used.");
    QUERY->add_mfun(QUERY, encode4_coefficients, "void", "sh");
    QUERY->add_arg(QUERY, "float[]", "coordinates");
    QUERY->doc_func(QUERY, "Set 1D array of all spherical harmonics currently being used.");
    QUERY->add_mfun(QUERY, encode4_seti, "void", "sh");
    QUERY->add_arg(QUERY, "float", "value");
    QUERY->add_arg(QUERY, "int", "n");
    QUERY->doc_func(QUERY, "Set nth spherical harmonic to be used.");
    QUERY->add_mfun(QUERY, encode4_position, "void", "pos");
    QUERY->add_arg(QUERY, "float", "azimuth");
    QUERY->add_arg(QUERY, "float", "zenith");
    QUERY->add_mfun(QUERY, encode4_getSH, "float[]", "sh");
    QUERY->doc_func(QUERY, "Get 1D array of all spherical harmonics currently being used.");
    QUERY->add_mfun(QUERY, encode4_getAzi, "float", "azi");
    QUERY->doc_func(QUERY, "Get last given azimuth.");
    QUERY->add_mfun(QUERY, encode4_getZeni, "float", "zeni");
    QUERY->doc_func(QUERY, "Get last given zenith.");
    QUERY->add_mfun(QUERY, encode4_setAzi, "float", "azi");
    QUERY->add_arg(QUERY, "float", "azimuth");
    QUERY->doc_func(QUERY, "Set azimuth.");
    QUERY->add_mfun(QUERY, encode4_setZeni, "float", "zeni");
    QUERY->add_arg(QUERY, "float", "zenith");
    QUERY->doc_func(QUERY, "Set zenith.");
    QUERY->add_mfun(QUERY, encode4_setWeights, "void", "weights");
    QUERY->add_arg(QUERY, "float[]", "weights");
    QUERY->doc_func(QUERY,"Set 1D array of weighting for all spherical harmonics.");
    QUERY->add_mfun(QUERY, encode4_getWeights, "float[]", "weights");
    QUERY->doc_func(QUERY,"Get 1D array of weighting for all spherical harmonics.");
    // this reserves a variable in the ChucK internal class to store
    // referene to the c++ class we defined above
    encode4_data_offset = QUERY->add_mvar(QUERY, "int", "@e_data", false);
    QUERY->end_class(QUERY);

    // ------------------------------------------------------------------------
    // begin class definition(s) Encode5; will be compiled, verified,
    // and added to the chuck host type system for use
    // ------------------------------------------------------------------------
    // NOTE to create a non-UGen class, change the second argument
    // to extend a different ChucK class (e.g., "Object")
    QUERY->begin_class(QUERY, "Encode5", "UGen");
    QUERY->doc_class(QUERY, "A fifth order ambisonic virtual source encoder.");
    // register the destructor (probably no need to change)
    QUERY->add_ctor(QUERY, encode5_ctor);
    QUERY->add_dtor(QUERY, encode5_dtor);
    QUERY->add_ugen_funcf(QUERY, encode5_tickf, NULL, 1, 36);
    QUERY->add_mfun(QUERY, encode5_geti, "float", "sh");
    QUERY->add_arg(QUERY, "int", "n");
    QUERY->doc_func(QUERY, "Get nth spherical harmonic currently being used.");
    QUERY->add_mfun(QUERY, encode5_coefficients, "void", "sh");
    QUERY->add_arg(QUERY, "float[]", "coordinates");
    QUERY->doc_func(QUERY, "Set 1D array of all spherical harmonics currently being used.");
    QUERY->add_mfun(QUERY, encode5_seti, "void", "sh");
    QUERY->add_arg(QUERY, "float", "value");
    QUERY->add_arg(QUERY, "int", "n");
    QUERY->doc_func(QUERY, "Set nth spherical harmonic to be used.");
    QUERY->add_mfun(QUERY, encode5_position, "void", "pos");
    QUERY->add_arg(QUERY, "float", "azimuth");
    QUERY->add_arg(QUERY, "float", "zenith");
    QUERY->add_mfun(QUERY, encode5_getSH, "float[]", "sh");
    QUERY->doc_func(QUERY, "Get 1D array of all spherical harmonics currently being used.");
    QUERY->add_mfun(QUERY, encode5_getAzi, "float", "azi");
    QUERY->doc_func(QUERY, "Get last given azimuth.");
    QUERY->add_mfun(QUERY, encode5_getZeni, "float", "zeni");
    QUERY->doc_func(QUERY, "Get last given zenith.");
    QUERY->add_mfun(QUERY, encode5_setAzi, "float", "azi");
    QUERY->add_arg(QUERY, "float", "azimuth");
    QUERY->doc_func(QUERY, "Set azimuth.");
    QUERY->add_mfun(QUERY, encode5_setZeni, "float", "zeni");
    QUERY->add_arg(QUERY, "float", "zenith");
    QUERY->doc_func(QUERY, "Set zenith.");
    QUERY->add_mfun(QUERY, encode5_setWeights, "void", "weights");
    QUERY->add_arg(QUERY, "float[]", "weights");
    QUERY->doc_func(QUERY,"Set 1D array of weighting for all spherical harmonics.");
    QUERY->add_mfun(QUERY, encode5_getWeights, "float[]", "weights");
    QUERY->doc_func(QUERY,"Get 1D array of weighting for all spherical harmonics.");
    // this reserves a variable in the ChucK internal class to store
    // referene to the c++ class we defined above
    encode5_data_offset = QUERY->add_mvar(QUERY, "int", "@e_data", false);
    QUERY->end_class(QUERY);

    // ------------------------------------------------------------------------
    // end the class(es) definition
    // IMPORTANT: this MUST be called to each class definition!
    // ------------------------------------------------------------------------

    // wasn't that a breeze?
    return TRUE;
}

//=================================================//
// ************************************************//
//                                                 //
// Encode1 DLL definitions ; Everett M. Carpenter  //
//                                                 //
// ************************************************//
//=================================================//
// implementation for the default constructor
CK_DLL_CTOR(encode1_ctor)
{
    // get the offset where we'll store our internal c++ class pointer
    OBJ_MEMBER_INT(SELF, encode1_data_offset) = 0;

    // instantiate our internal c++ class representation
    Encode1 *encode_obj = new Encode1(API->vm->srate(VM));

    // store the pointer in the ChucK object member
    OBJ_MEMBER_INT(SELF, encode1_data_offset) = (t_CKINT)encode_obj;
}

// implementation for the destructor
CK_DLL_DTOR(encode1_dtor)
{
    // get our c++ class pointer
    Encode1 *encode_obj = (Encode1 *)OBJ_MEMBER_INT(SELF, encode1_data_offset);
    // clean up (this macro tests for NULL, deletes, and zeros out the variable)
    CK_SAFE_DELETE(encode_obj);
    // set the data field to 0
    OBJ_MEMBER_INT(SELF, encode1_data_offset) = 0;
}

CK_DLL_MFUN(encode1_geti)
{
    int index = GET_NEXT_INT(ARGS);
    // get our c++ class pointer
    Encode1 *encode_obj = (Encode1 *)OBJ_MEMBER_INT(SELF, encode1_data_offset);
    if (encode_obj)
    {
        RETURN->v_float = encode_obj->get_i(index);
    }
}

// implementation for tick function (relevant only for UGens)
CK_DLL_TICKF(encode1_tickf)
{
    // get our c++ class pointer
    Encode1 *encode_obj = (Encode1 *)OBJ_MEMBER_INT(SELF, encode1_data_offset);

    // invoke our tick function; store in the magical out variable
    if (encode_obj)
    {
        encode_obj->tick(in, out, nframes);
    }
    // yes
    return TRUE;
}

CK_DLL_MFUN(encode1_coefficients)
{
    // get our c++ class pointer
    Encode1 *encode_obj = (Encode1 *)OBJ_MEMBER_INT(SELF, encode1_data_offset);
    Chuck_ArrayFloat *coefficients = (Chuck_ArrayFloat *)GET_NEXT_OBJECT(ARGS);
    encode_obj->set_coefficients(coefficients, API);
}

CK_DLL_MFUN(encode1_seti)
{
    float input_value = GET_NEXT_FLOAT(ARGS);
    int input_index = GET_NEXT_INT(ARGS);
    // get our c++ class pointer
    Encode1 *encode_obj = (Encode1 *)OBJ_MEMBER_INT(SELF, encode1_data_offset);
    if (encode_obj)
    {
        encode_obj->set_i(input_value, input_index);
    }
}

CK_DLL_MFUN(encode1_position)
{
    float azi = GET_NEXT_FLOAT(ARGS);
    float zeni = GET_NEXT_FLOAT(ARGS);
    // get c++ class pointer
    Encode1 *encode_obj = (Encode1 *)OBJ_MEMBER_INT(SELF, encode1_data_offset);
    if (encode_obj)
    {
        encode_obj->position(azi, zeni);
    }
}

CK_DLL_MFUN(encode1_getSH)
{
    // get our c++ class pointer
    Encode1 *encode_obj = (Encode1 *)OBJ_MEMBER_INT(SELF, encode1_data_offset);

    std::vector<float> sphericals = encode_obj->getSH();

    // Create a float[] array
    Chuck_DL_Api::Object returnarray = API->object->create(SHRED, API->type->lookup(VM, "float[]"), false);
    Chuck_ArrayFloat *coordinatearray = (Chuck_ArrayFloat *)returnarray;
    for (int i = 0; i < sphericals.size(); i++)
    {
        API->object->array_float_push_back(coordinatearray, sphericals[i]);
    }

    RETURN->v_object = (Chuck_Object *)coordinatearray;
}

CK_DLL_MFUN(encode1_setWeights)
{
    Chuck_ArrayFloat *weights = (Chuck_ArrayFloat *)GET_NEXT_OBJECT(ARGS);
    // get our c++ class pointer
    Encode1 *encode1_obj = (Encode1 *)OBJ_MEMBER_INT(SELF, encode1_data_offset);
    if (encode1_obj)
        encode1_obj->CKsetWeights(weights, API);
}

CK_DLL_MFUN(encode1_getWeights)
{
    // get our c++ class pointer
    Encode1 *encode_obj = (Encode1 *)OBJ_MEMBER_INT(SELF, encode1_data_offset);

    std::vector<float> weights = encode_obj->getWeights();

    // Create a float[] array
    Chuck_DL_Api::Object returnarray = API->object->create(SHRED, API->type->lookup(VM, "float[]"), false);
    Chuck_ArrayFloat *coordinatearray = (Chuck_ArrayFloat *)returnarray;
    for (int i = 0; i < weights.size(); i++)
    {
        API->object->array_float_push_back(coordinatearray, weights[i]);
    }

    RETURN->v_object = (Chuck_Object *)coordinatearray;
}

CK_DLL_MFUN(encode1_getAzi)
{
    Encode1* encode_obj = (Encode1*)OBJ_MEMBER_INT(SELF, encode1_data_offset);
    if (encode_obj) RETURN->v_float = encode_obj->last_azimuth;
}

CK_DLL_MFUN(encode1_getZeni)
{
    Encode1* encode_obj = (Encode1*)OBJ_MEMBER_INT(SELF, encode1_data_offset);
    if (encode_obj) RETURN->v_float = encode_obj->last_zenith;
}

CK_DLL_MFUN(encode1_setAzi)
{
    Encode1* encode_obj = (Encode1*)OBJ_MEMBER_INT(SELF, encode1_data_offset);
    float azi = GET_NEXT_FLOAT(ARGS);
    if (encode_obj) encode_obj->position(azi, encode_obj->last_zenith);
}

CK_DLL_MFUN(encode1_setZeni)
{
    Encode1* encode_obj = (Encode1*)OBJ_MEMBER_INT(SELF, encode1_data_offset);
    float zeni = GET_NEXT_FLOAT(ARGS);
    if (encode_obj) encode_obj->position(encode_obj->last_azimuth, zeni);
}

//=================================================//
// ************************************************//
//                                                 //
// Encode2 DLL definitions ; Everett M. Carpenter  //
//                                                 //
// ************************************************//
//=================================================//
// implementation for the default constructor
CK_DLL_CTOR(encode2_ctor)
{
    // get the offset where we'll store our internal c++ class pointer
    OBJ_MEMBER_INT(SELF, encode2_data_offset) = 0;

    // instantiate our internal c++ class representation
    Encode2 *encode_obj = new Encode2(API->vm->srate(VM));

    // store the pointer in the ChucK object member
    OBJ_MEMBER_INT(SELF, encode2_data_offset) = (t_CKINT)encode_obj;
}

// implementation for the destructor
CK_DLL_DTOR(encode2_dtor)
{
    // get our c++ class pointer
    Encode2 *encode_obj = (Encode2 *)OBJ_MEMBER_INT(SELF, encode2_data_offset);
    // clean up (this macro tests for NULL, deletes, and zeros out the variable)
    CK_SAFE_DELETE(encode_obj);
    // set the data field to 0
    OBJ_MEMBER_INT(SELF, encode2_data_offset) = 0;
}

// implementation for tick function (relevant only for UGens)
CK_DLL_TICKF(encode2_tickf)
{
    // get our c++ class pointer
    Encode2 *encode_obj = (Encode2 *)OBJ_MEMBER_INT(SELF, encode2_data_offset);

    // invoke our tick function; store in the magical out variable
    if (encode_obj)
    {
        encode_obj->tick(in, out, nframes);
    }
    // yes
    return TRUE;
}

CK_DLL_MFUN(encode2_geti)
{
    int index = GET_NEXT_INT(ARGS);
    // get our c++ class pointer
    Encode2 *encode_obj = (Encode2 *)OBJ_MEMBER_INT(SELF, encode2_data_offset);
    if (encode_obj)
    {
        RETURN->v_float = encode_obj->get_i(index);
    }
}

CK_DLL_MFUN(encode2_coefficients)
{
    // get our c++ class pointer
    Encode2 *encode_obj = (Encode2 *)OBJ_MEMBER_INT(SELF, encode2_data_offset);
    Chuck_ArrayFloat *coefficients = (Chuck_ArrayFloat *)GET_NEXT_OBJECT(ARGS);
    encode_obj->set_coefficients(coefficients, API);
}

CK_DLL_MFUN(encode2_seti)
{
    float input_value = GET_NEXT_FLOAT(ARGS);
    int input_index = GET_NEXT_INT(ARGS);
    // get our c++ class pointer
    Encode2 *encode_obj = (Encode2 *)OBJ_MEMBER_INT(SELF, encode2_data_offset);
    if (encode_obj)
    {
        encode_obj->set_i(input_value, input_index);
    }
}

CK_DLL_MFUN(encode2_position)
{
    float azi = GET_NEXT_FLOAT(ARGS);
    float zeni = GET_NEXT_FLOAT(ARGS);
    // get c++ class pointer
    Encode2 *encode_obj = (Encode2 *)OBJ_MEMBER_INT(SELF, encode2_data_offset);
    if (encode_obj)
    {
        encode_obj->position(azi, zeni);
    }
}

CK_DLL_MFUN(encode2_getSH)
{
    // get our c++ class pointer
    Encode2 *encode_obj = (Encode2 *)OBJ_MEMBER_INT(SELF, encode2_data_offset);

    std::vector<float> sphericals = encode_obj->getSH();

    // Create a float[] array
    Chuck_DL_Api::Object returnarray = API->object->create(SHRED, API->type->lookup(VM, "float[]"), false);
    Chuck_ArrayFloat *coordinatearray = (Chuck_ArrayFloat *)returnarray;
    for (int i = 0; i < sphericals.size(); i++)
    {
        API->object->array_float_push_back(coordinatearray, sphericals[i]);
    }

    RETURN->v_object = (Chuck_Object *)coordinatearray;
}

CK_DLL_MFUN(encode2_setWeights)
{
    Chuck_ArrayFloat *weights = (Chuck_ArrayFloat *)GET_NEXT_OBJECT(ARGS);
    // get our c++ class pointer
    Encode2 *encode_obj = (Encode2 *)OBJ_MEMBER_INT(SELF, encode2_data_offset);
    if (encode_obj)
        encode_obj->CKsetWeights(weights, API);
}

CK_DLL_MFUN(encode2_getWeights)
{
    // get our c++ class pointer
    Encode2 *encode_obj = (Encode2 *)OBJ_MEMBER_INT(SELF, encode2_data_offset);

    std::vector<float> weights = encode_obj->getWeights();

    // Create a float[] array
    Chuck_DL_Api::Object returnarray = API->object->create(SHRED, API->type->lookup(VM, "float[]"), false);
    Chuck_ArrayFloat *coordinatearray = (Chuck_ArrayFloat *)returnarray;
    for (int i = 0; i < weights.size(); i++)
    {
        API->object->array_float_push_back(coordinatearray, weights[i]);
    }

    RETURN->v_object = (Chuck_Object *)coordinatearray;
}

CK_DLL_MFUN(encode2_getAzi)
{
    Encode2* encode_obj = (Encode2*)OBJ_MEMBER_INT(SELF, encode2_data_offset);
    if (encode_obj) RETURN->v_float = encode_obj->last_azimuth;
}

CK_DLL_MFUN(encode2_getZeni)
{
    Encode2* encode_obj = (Encode2*)OBJ_MEMBER_INT(SELF, encode2_data_offset);
    if (encode_obj) RETURN->v_float = encode_obj->last_zenith;
}

CK_DLL_MFUN(encode2_setAzi)
{
    Encode2* encode_obj = (Encode2*)OBJ_MEMBER_INT(SELF, encode2_data_offset);
    float azi = GET_NEXT_FLOAT(ARGS);
    if (encode_obj) encode_obj->position(azi, encode_obj->last_zenith);
}

CK_DLL_MFUN(encode2_setZeni)
{
    Encode2* encode_obj = (Encode2*)OBJ_MEMBER_INT(SELF, encode2_data_offset);
    float zeni = GET_NEXT_FLOAT(ARGS);
    if (encode_obj) encode_obj->position(encode_obj->last_azimuth, zeni);
}

//=================================================//
// ************************************************//
//                                                 //
// Encode3 DLL definitions ; Everett M. Carpenter  //
//                                                 //
// ************************************************//
//=================================================//
// implementation for the default constructor
CK_DLL_CTOR(encode3_ctor)
{
    // get the offset where we'll store our internal c++ class pointer
    OBJ_MEMBER_INT(SELF, encode3_data_offset) = 0;

    // instantiate our internal c++ class representation
    Encode3 *encode_obj = new Encode3(API->vm->srate(VM));

    // store the pointer in the ChucK object member
    OBJ_MEMBER_INT(SELF, encode3_data_offset) = (t_CKINT)encode_obj;
}

// implementation for the destructor
CK_DLL_DTOR(encode3_dtor)
{
    // get our c++ class pointer
    Encode3 *encode_obj = (Encode3 *)OBJ_MEMBER_INT(SELF, encode3_data_offset);
    // clean up (this macro tests for NULL, deletes, and zeros out the variable)
    CK_SAFE_DELETE(encode_obj);
    // set the data field to 0
    OBJ_MEMBER_INT(SELF, encode3_data_offset) = 0;
}

// implementation for tick function (relevant only for UGens)
CK_DLL_TICKF(encode3_tickf)
{
    // get our c++ class pointer
    Encode3 *encode_obj = (Encode3 *)OBJ_MEMBER_INT(SELF, encode3_data_offset);

    // invoke our tick function; store in the magical out variable
    if (encode_obj)
    {
        encode_obj->tick(in, out, nframes);
    }
    // yes
    return TRUE;
}

CK_DLL_MFUN(encode3_geti)
{
    int index = GET_NEXT_INT(ARGS);
    // get our c++ class pointer
    Encode3 *encode_obj = (Encode3 *)OBJ_MEMBER_INT(SELF, encode3_data_offset);
    if (encode_obj)
    {
        RETURN->v_float = encode_obj->get_i(index);
    }
}

CK_DLL_MFUN(encode3_coefficients)
{
    // get our c++ class pointer
    Encode3 *encode_obj = (Encode3 *)OBJ_MEMBER_INT(SELF, encode3_data_offset);
    Chuck_ArrayFloat *coefficients = (Chuck_ArrayFloat *)GET_NEXT_OBJECT(ARGS);
    encode_obj->set_coefficients(coefficients, API);
}

CK_DLL_MFUN(encode3_seti)
{
    float input_value = GET_NEXT_FLOAT(ARGS);
    int input_index = GET_NEXT_INT(ARGS);
    // get our c++ class pointer
    Encode3 *encode_obj = (Encode3 *)OBJ_MEMBER_INT(SELF, encode3_data_offset);
    if (encode_obj)
    {
        encode_obj->set_i(input_value, input_index);
    }
}

CK_DLL_MFUN(encode3_position)
{
    float azi = GET_NEXT_FLOAT(ARGS);
    float zeni = GET_NEXT_FLOAT(ARGS);
    // get c++ class pointer
    Encode3 *encode_obj = (Encode3 *)OBJ_MEMBER_INT(SELF, encode3_data_offset);
    if (encode_obj)
    {
        encode_obj->position(azi, zeni);
    }
}

CK_DLL_MFUN(encode3_getSH)
{
    // get our c++ class pointer
    Encode3 *encode_obj = (Encode3 *)OBJ_MEMBER_INT(SELF, encode3_data_offset);

    std::vector<float> sphericals = encode_obj->getSH();

    // Create a float[] array
    Chuck_DL_Api::Object returnarray = API->object->create(SHRED, API->type->lookup(VM, "float[]"), false);
    Chuck_ArrayFloat *coordinatearray = (Chuck_ArrayFloat *)returnarray;
    for (int i = 0; i < sphericals.size(); i++)
    {
        API->object->array_float_push_back(coordinatearray, sphericals[i]);
    }

    RETURN->v_object = (Chuck_Object *)coordinatearray;
}

CK_DLL_MFUN(encode3_setWeights)
{
    Chuck_ArrayFloat *weights = (Chuck_ArrayFloat *)GET_NEXT_OBJECT(ARGS);
    // get our c++ class pointer
    Encode3 *encode3_obj = (Encode3 *)OBJ_MEMBER_INT(SELF, encode3_data_offset);
    if (encode3_obj)
        encode3_obj->CKsetWeights(weights, API);
}

CK_DLL_MFUN(encode3_getWeights)
{
    // get our c++ class pointer
    Encode3 *encode_obj = (Encode3 *)OBJ_MEMBER_INT(SELF, encode3_data_offset);

    std::vector<float> weights = encode_obj->getWeights();

    // Create a float[] array
    Chuck_DL_Api::Object returnarray = API->object->create(SHRED, API->type->lookup(VM, "float[]"), false);
    Chuck_ArrayFloat *coordinatearray = (Chuck_ArrayFloat *)returnarray;
    for (int i = 0; i < weights.size(); i++)
    {
        API->object->array_float_push_back(coordinatearray, weights[i]);
    }

    RETURN->v_object = (Chuck_Object *)coordinatearray;
}

CK_DLL_MFUN(encode3_getAzi)
{
    Encode3* encode_obj = (Encode3*)OBJ_MEMBER_INT(SELF, encode3_data_offset);
    if (encode_obj) RETURN->v_float = encode_obj->last_azimuth;
}

CK_DLL_MFUN(encode3_getZeni)
{
    Encode3* encode_obj = (Encode3*)OBJ_MEMBER_INT(SELF, encode3_data_offset);
    if (encode_obj) RETURN->v_float = encode_obj->last_zenith;
}

CK_DLL_MFUN(encode3_setAzi)
{
    Encode3* encode_obj = (Encode3*)OBJ_MEMBER_INT(SELF, encode3_data_offset);
    float azi = GET_NEXT_FLOAT(ARGS);
    if (encode_obj) encode_obj->position(azi, encode_obj->last_zenith);
}

CK_DLL_MFUN(encode3_setZeni)
{
    Encode3* encode_obj = (Encode3*)OBJ_MEMBER_INT(SELF, encode3_data_offset);
    float zeni = GET_NEXT_FLOAT(ARGS);
    if (encode_obj) encode_obj->position(encode_obj->last_azimuth, zeni);
}

//=================================================//
// ************************************************//
//                                                 //
// Encode4 DLL definitions ; Everett M. Carpenter  //
//                                                 //
// ************************************************//
//=================================================//
// implementation for the default constructor
CK_DLL_CTOR(encode4_ctor)
{
    // get the offset where we'll store our internal c++ class pointer
    OBJ_MEMBER_INT(SELF, encode4_data_offset) = 0;

    // instantiate our internal c++ class representation
    Encode4 *encode_obj = new Encode4(API->vm->srate(VM));

    // store the pointer in the ChucK object member
    OBJ_MEMBER_INT(SELF, encode4_data_offset) = (t_CKINT)encode_obj;
}

// implementation for the destructor
CK_DLL_DTOR(encode4_dtor)
{
    // get our c++ class pointer
    Encode4 *encode_obj = (Encode4 *)OBJ_MEMBER_INT(SELF, encode4_data_offset);
    // clean up (this macro tests for NULL, deletes, and zeros out the variable)
    CK_SAFE_DELETE(encode_obj);
    // set the data field to 0
    OBJ_MEMBER_INT(SELF, encode4_data_offset) = 0;
}

// implementation for tick function (relevant only for UGens)
CK_DLL_TICKF(encode4_tickf)
{
    // get our c++ class pointer
    Encode4 *encode_obj = (Encode4 *)OBJ_MEMBER_INT(SELF, encode4_data_offset);

    // invoke our tick function; store in the magical out variable
    if (encode_obj)
    {
        encode_obj->tick(in, out, nframes);
    }
    // yes
    return TRUE;
}

CK_DLL_MFUN(encode4_geti)
{
    int index = GET_NEXT_INT(ARGS);
    // get our c++ class pointer
    Encode4 *encode_obj = (Encode4 *)OBJ_MEMBER_INT(SELF, encode4_data_offset);
    if (encode_obj)
    {
        RETURN->v_float = encode_obj->get_i(index);
    }
}

CK_DLL_MFUN(encode4_coefficients)
{
    // get our c++ class pointer
    Encode4 *encode_obj = (Encode4 *)OBJ_MEMBER_INT(SELF, encode4_data_offset);
    Chuck_ArrayFloat *coefficients = (Chuck_ArrayFloat *)GET_NEXT_OBJECT(ARGS);
    encode_obj->set_coefficients(coefficients, API);
}

CK_DLL_MFUN(encode4_seti)
{
    float input_value = GET_NEXT_FLOAT(ARGS);
    int input_index = GET_NEXT_INT(ARGS);
    // get our c++ class pointer
    Encode4 *encode_obj = (Encode4 *)OBJ_MEMBER_INT(SELF, encode4_data_offset);
    if (encode_obj)
    {
        encode_obj->set_i(input_value, input_index);
    }
}

CK_DLL_MFUN(encode4_position)
{
    float azi = GET_NEXT_FLOAT(ARGS);
    float zeni = GET_NEXT_FLOAT(ARGS);
    // get c++ class pointer
    Encode4 *encode_obj = (Encode4 *)OBJ_MEMBER_INT(SELF, encode4_data_offset);
    if (encode_obj)
    {
        encode_obj->position(azi, zeni);
    }
}

CK_DLL_MFUN(encode4_getSH)
{
    // get our c++ class pointer
    Encode4 *encode_obj = (Encode4 *)OBJ_MEMBER_INT(SELF, encode4_data_offset);

    std::vector<float> sphericals = encode_obj->getSH();

    // Create a float[] array
    Chuck_DL_Api::Object returnarray = API->object->create(SHRED, API->type->lookup(VM, "float[]"), false);
    Chuck_ArrayFloat *coordinatearray = (Chuck_ArrayFloat *)returnarray;
    for (int i = 0; i < sphericals.size(); i++)
    {
        API->object->array_float_push_back(coordinatearray, sphericals[i]);
    }

    RETURN->v_object = (Chuck_Object *)coordinatearray;
}

CK_DLL_MFUN(encode4_setWeights)
{
    Chuck_ArrayFloat *weights = (Chuck_ArrayFloat *)GET_NEXT_OBJECT(ARGS);
    // get our c++ class pointer
    Encode4 *encode4_obj = (Encode4 *)OBJ_MEMBER_INT(SELF, encode4_data_offset);
    if (encode4_obj)
        encode4_obj->CKsetWeights(weights, API);
}

CK_DLL_MFUN(encode4_getWeights)
{
    // get our c++ class pointer
    Encode4 *encode_obj = (Encode4 *)OBJ_MEMBER_INT(SELF, encode4_data_offset);

    std::vector<float> weights = encode_obj->getWeights();

    // Create a float[] array
    Chuck_DL_Api::Object returnarray = API->object->create(SHRED, API->type->lookup(VM, "float[]"), false);
    Chuck_ArrayFloat *coordinatearray = (Chuck_ArrayFloat *)returnarray;
    for (int i = 0; i < weights.size(); i++)
    {
        API->object->array_float_push_back(coordinatearray, weights[i]);
    }

    RETURN->v_object = (Chuck_Object *)coordinatearray;
}

CK_DLL_MFUN(encode4_getAzi)
{
    Encode4* encode_obj = (Encode4*)OBJ_MEMBER_INT(SELF, encode4_data_offset);
    if (encode_obj) RETURN->v_float = encode_obj->last_azimuth;
}

CK_DLL_MFUN(encode4_getZeni)
{
    Encode4* encode_obj = (Encode4*)OBJ_MEMBER_INT(SELF, encode4_data_offset);
    if (encode_obj) RETURN->v_float = encode_obj->last_zenith;
}

CK_DLL_MFUN(encode4_setAzi)
{
    Encode4* encode_obj = (Encode4*)OBJ_MEMBER_INT(SELF, encode4_data_offset);
    float azi = GET_NEXT_FLOAT(ARGS);
    if (encode_obj) encode_obj->position(azi, encode_obj->last_zenith);
}

CK_DLL_MFUN(encode4_setZeni)
{
    Encode4* encode_obj = (Encode4*)OBJ_MEMBER_INT(SELF, encode4_data_offset);
    float zeni = GET_NEXT_FLOAT(ARGS);
    if (encode_obj) encode_obj->position(encode_obj->last_azimuth, zeni);
}

//=================================================//
// ************************************************//
//                                                 //
// Encode5 DLL definitions ; Everett M. Carpenter  //
//                                                 //
// ************************************************//
//=================================================//
// implementation for the default constructor
CK_DLL_CTOR(encode5_ctor)
{
    // get the offset where we'll store our internal c++ class pointer
    OBJ_MEMBER_INT(SELF, encode5_data_offset) = 0;

    // instantiate our internal c++ class representation
    Encode5 *encode_obj = new Encode5(API->vm->srate(VM));

    // store the pointer in the ChucK object member
    OBJ_MEMBER_INT(SELF, encode5_data_offset) = (t_CKINT)encode_obj;
}

// implementation for the destructor
CK_DLL_DTOR(encode5_dtor)
{
    // get our c++ class pointer
    Encode5 *encode_obj = (Encode5 *)OBJ_MEMBER_INT(SELF, encode5_data_offset);
    // clean up (this macro tests for NULL, deletes, and zeros out the variable)
    CK_SAFE_DELETE(encode_obj);
    // set the data field to 0
    OBJ_MEMBER_INT(SELF, encode5_data_offset) = 0;
}

// implementation for tick function (relevant only for UGens)
CK_DLL_TICKF(encode5_tickf)
{
    // get our c++ class pointer
    Encode5 *encode_obj = (Encode5 *)OBJ_MEMBER_INT(SELF, encode5_data_offset);

    // invoke our tick function; store in the magical out variable
    if (encode_obj)
    {
        encode_obj->tick(in, out, nframes);
    }
    // yes
    return TRUE;
}

CK_DLL_MFUN(encode5_geti)
{
    int index = GET_NEXT_INT(ARGS);
    // get our c++ class pointer
    Encode5 *encode_obj = (Encode5 *)OBJ_MEMBER_INT(SELF, encode5_data_offset);
    if (encode_obj)
    {
        RETURN->v_float = encode_obj->get_i(index);
    }
}

CK_DLL_MFUN(encode5_coefficients)
{
    // get our c++ class pointer
    Encode5 *encode_obj = (Encode5 *)OBJ_MEMBER_INT(SELF, encode5_data_offset);
    Chuck_ArrayFloat *coefficients = (Chuck_ArrayFloat *)GET_NEXT_OBJECT(ARGS);
    encode_obj->set_coefficients(coefficients, API);
}

CK_DLL_MFUN(encode5_seti)
{
    float input_value = GET_NEXT_FLOAT(ARGS);
    int input_index = GET_NEXT_INT(ARGS);
    // get our c++ class pointer
    Encode5 *encode_obj = (Encode5 *)OBJ_MEMBER_INT(SELF, encode5_data_offset);
    if (encode_obj)
    {
        encode_obj->set_i(input_value, input_index);
    }
}

CK_DLL_MFUN(encode5_position)
{
    float azi = GET_NEXT_FLOAT(ARGS);
    float zeni = GET_NEXT_FLOAT(ARGS);
    // get c++ class pointer
    Encode5 *encode_obj = (Encode5 *)OBJ_MEMBER_INT(SELF, encode5_data_offset);
    if (encode_obj)
    {
        encode_obj->position(azi, zeni);
    }
}

CK_DLL_MFUN(encode5_getSH)
{
    // get our c++ class pointer
    Encode5 *encode_obj = (Encode5 *)OBJ_MEMBER_INT(SELF, encode5_data_offset);

    std::vector<float> sphericals = encode_obj->getSH();

    // Create a float[] array
    Chuck_DL_Api::Object returnarray = API->object->create(SHRED, API->type->lookup(VM, "float[]"), false);
    Chuck_ArrayFloat *coordinatearray = (Chuck_ArrayFloat *)returnarray;
    for (int i = 0; i < sphericals.size(); i++)
    {
        API->object->array_float_push_back(coordinatearray, sphericals[i]);
    }

    RETURN->v_object = (Chuck_Object *)coordinatearray;
}

CK_DLL_MFUN(encode5_setWeights)
{
    Chuck_ArrayFloat *weights = (Chuck_ArrayFloat *)GET_NEXT_OBJECT(ARGS);
    // get our c++ class pointer
    Encode5 *encode5_obj = (Encode5 *)OBJ_MEMBER_INT(SELF, encode5_data_offset);
    if (encode5_obj)
        encode5_obj->CKsetWeights(weights, API);
}

CK_DLL_MFUN(encode5_getWeights)
{
    // get our c++ class pointer
    Encode5 *encode_obj = (Encode5 *)OBJ_MEMBER_INT(SELF, encode5_data_offset);

    std::vector<float> weights = encode_obj->getWeights();

    // Create a float[] array
    Chuck_DL_Api::Object returnarray = API->object->create(SHRED, API->type->lookup(VM, "float[]"), false);
    Chuck_ArrayFloat *coordinatearray = (Chuck_ArrayFloat *)returnarray;
    for (int i = 0; i < weights.size(); i++)
    {
        API->object->array_float_push_back(coordinatearray, weights[i]);
    }

    RETURN->v_object = (Chuck_Object *)coordinatearray;
}

CK_DLL_MFUN(encode5_getAzi)
{
    Encode5 *encode_obj = (Encode5*)OBJ_MEMBER_INT(SELF, encode5_data_offset);
    if (encode_obj) RETURN->v_float = encode_obj->last_azimuth;
}

CK_DLL_MFUN(encode5_getZeni)
{
    Encode5* encode_obj = (Encode5*)OBJ_MEMBER_INT(SELF, encode5_data_offset);
    if (encode_obj) RETURN->v_float = encode_obj->last_zenith;
}

CK_DLL_MFUN(encode5_setAzi)
{
    Encode5* encode_obj = (Encode5*)OBJ_MEMBER_INT(SELF, encode5_data_offset);
    float azi = GET_NEXT_FLOAT(ARGS);
    if (encode_obj) encode_obj->position(azi, encode_obj->last_zenith);
}

CK_DLL_MFUN(encode5_setZeni)
{
    Encode5* encode_obj = (Encode5*)OBJ_MEMBER_INT(SELF, encode5_data_offset);
    float zeni = GET_NEXT_FLOAT(ARGS);
    if (encode_obj) encode_obj->position(encode_obj->last_azimuth, zeni);
}

//=================================================//
