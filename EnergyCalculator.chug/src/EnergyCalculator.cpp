//-----------------------------------------------------------------------------
// happy chucking & chugging!
//-----------------------------------------------------------------------------

// include chugin header
#include "../include/chugin.h"
#include "../include/EnergyCalculator.h"

// general includes
#include <iostream>


// declaration of chugin constructor
CK_DLL_CTOR( energycalculator_ctor );
// declaration of chugin desctructor
CK_DLL_DTOR( energycalculator_dtor );

// example of getter/setter
CK_DLL_MFUN( energycalculator_setTimeConstant );
CK_DLL_MFUN( energycalculator_getTimeConstant );

CK_DLL_MFUN( energycalculator_setOrder );
CK_DLL_MFUN( energycalculator_getOrder );

// for chugins extending UGen, this is mono synthesis function for 1 sample
CK_DLL_TICKF( energycalculator_tick );

// this is a special offset reserved for chugin internal data
t_CKINT energycalculator_data_offset = 0;
t_CKINT myOrder = 0; // from mcdonalds
t_CKDUR myConstant = 0;

//-----------------------------------------------------------------------------
// info function: ChucK calls this when loading/probing the chugin
// NOTE: please customize these info fields below; they will be used for
// chugins loading, probing, and package management and documentation
//-----------------------------------------------------------------------------
CK_DLL_INFO( EnergyCalculator )
{
    // the version string of this chugin, e.g., "v1.2.1"
    QUERY->setinfo( QUERY, CHUGIN_INFO_CHUGIN_VERSION, "" );
    // the author(s) of this chugin, e.g., "Alice Baker & Carl Donut"
    QUERY->setinfo( QUERY, CHUGIN_INFO_AUTHORS, "IEM => ChucK by emc" );
    // text description of this chugin; what is it? what does it do? who is it for?
    QUERY->setinfo( QUERY, CHUGIN_INFO_DESCRIPTION, "" );
    // (optional) URL of the homepage for this chugin
    QUERY->setinfo( QUERY, CHUGIN_INFO_URL, "" );
    // (optional) contact email
    QUERY->setinfo( QUERY, CHUGIN_INFO_EMAIL, "" );
}


//-----------------------------------------------------------------------------
// query function: ChucK calls this when loading the chugin
// modify this function to define this chugin's API and language extensions
//-----------------------------------------------------------------------------
CK_DLL_QUERY( EnergyCalculator )
{
    // generally, don't change this...
    QUERY->setname( QUERY, "EnergyCalculator" );

    // ------------------------------------------------------------------------
    // begin class definition(s); will be compiled, verified,
    // and added to the chuck host type system for use
    // ------------------------------------------------------------------------
    // NOTE to create a non-UGen class, change the second argument
    // to extend a different ChucK class (e.g., "Object")
    QUERY->begin_class( QUERY, "EnergyCalculator", "UGen" );

    // register default constructor
    QUERY->add_ctor( QUERY, energycalculator_ctor );
    // NOTE constructors can be overloaded like any other functions,
    // each overloaded constructor begins with `QUERY->add_ctor()`
    // followed by a sequence of `QUERY->add_arg()`

    // register the destructor (probably no need to change)
    QUERY->add_dtor( QUERY, energycalculator_dtor );

    // for UGens only: add tick function
    // NOTE a non-UGen class should remove or comment out this next line
    QUERY->add_ugen_funcf( QUERY, energycalculator_tick, NULL, 64, 0 );
    // NOTE: if this is to be a UGen with more than 1 channel,
    // e.g., a multichannel UGen -- will need to use add_ugen_funcf()
    // and declare a tickf function using CK_DLL_TICKF

    // example of adding setter method
    QUERY->add_mfun( QUERY, energycalculator_setTimeConstant, "dur", "timeConstant" );
    // example of adding argument to the above method
    QUERY->add_arg( QUERY, "dur", "constant" );

    // example of adding getter method
    QUERY->add_mfun( QUERY, energycalculator_getTimeConstant, "dur", "timeConstant" );

    // example of adding setter method
    QUERY->add_mfun( QUERY, energycalculator_setOrder, "int", "order" );
    // example of adding argument to the above method
    QUERY->add_arg( QUERY, "int", "order" );

    // example of adding getter method
    QUERY->add_mfun( QUERY, energycalculator_getOrder, "int", "order" );
    
    // this reserves a variable in the ChucK internal class to store 
    // referene to the c++ class we defined above
    energycalculator_data_offset = QUERY->add_mvar( QUERY, "int", "@ec_data", false );

    // ------------------------------------------------------------------------
    // end the class definition
    // IMPORTANT: this MUST be called to each class definition!
    // ------------------------------------------------------------------------
    QUERY->end_class( QUERY );

    // wasn't that a breeze?
    return TRUE;
}


// implementation for the default constructor
CK_DLL_CTOR( energycalculator_ctor )
{
    // get the offset where we'll store our internal c++ class pointer
    OBJ_MEMBER_INT( SELF, energycalculator_data_offset ) = 0;
    
    // instantiate our internal c++ class representation
    EnergyCalculator * ec_obj = new EnergyCalculator( API->vm->srate(VM), 1024 );
    
    // store the pointer in the ChucK object member
    OBJ_MEMBER_INT( SELF, energycalculator_data_offset ) = (t_CKINT)ec_obj;
}


// implementation for the destructor
CK_DLL_DTOR( energycalculator_dtor )
{
    // get our c++ class pointer
    EnergyCalculator * ec_obj = (EnergyCalculator *)OBJ_MEMBER_INT( SELF, energycalculator_data_offset );
    // clean up (this macro tests for NULL, deletes, and zeros out the variable)
    CK_SAFE_DELETE( ec_obj );
    // set the data field to 0
    OBJ_MEMBER_INT( SELF, energycalculator_data_offset ) = 0;
}


// implementation for tick function (relevant only for UGens)
CK_DLL_TICKF( energycalculator_tick )
{
    // get our c++ class pointer
    EnergyCalculator * ec_obj = (EnergyCalculator *)OBJ_MEMBER_INT(SELF, energycalculator_data_offset);
 
    // invoke our tick function; store in the magical out variable
    if( ec_obj ) ec_obj->tick( in, out, myOrder, nframes );

    // yes
    return TRUE;
}


// example implementation for setter
CK_DLL_MFUN( energycalculator_setOrder )
{
    // get our c++ class pointer
    EnergyCalculator * ec_obj = (EnergyCalculator *)OBJ_MEMBER_INT( SELF, energycalculator_data_offset );

    // get next argument
    // NOTE argument type must match what is specified above in CK_DLL_QUERY
    // NOTE this advances the ARGS pointer, so save in variable for re-use
    t_CKINT arg1 = GET_NEXT_INT( ARGS );
    // check it
    if( arg1 < 0 )
    {
        API->vm->throw_exception( "Non-positive Order", "Order given as argument to EnergyCalculator.order() was negative.", SHRED );
    }
    else // cool
    {
        myOrder = arg1;
    }
    
    // call setParam() and set the return value
    RETURN->v_int = myOrder;
}


// example implementation for getter
CK_DLL_MFUN( energycalculator_getOrder )
{
    // get our c++ class pointer
    EnergyCalculator * ec_obj = (EnergyCalculator *)OBJ_MEMBER_INT( SELF, energycalculator_data_offset );

    // call getParam() and set the return value
    RETURN->v_int = myOrder;
}

