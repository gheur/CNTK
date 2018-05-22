cmake_minimum_required (VERSION 3.8)

include(../../../Tools/cmake/common.cmake REQUIRED)

EnsureProperties(CNTK_VERSION;CMAKE_BUILD_TYPE)

include(../../../Tools/cmake/csharp_common.cmake REQUIRED)

set(binary_name_suffix -${CNTK_VERSION}$<${is_debug}:d>)
set(binary_name Cntk.Core.CSBinding${binary_name_suffix})

set(source_filenames
    Helper.cs
    Utils.cs
    
    ShimApiClasses/AxisShim.cs
    ShimApiClasses/CNTKLibShim.cs
    ShimApiClasses/ConstantShim.cs
    ShimApiClasses/DeviceDescriptorShim.cs
    ShimApiClasses/FunctionShim.cs
    ShimApiClasses/LearnerShim.cs
    ShimApiClasses/MinibatchSourceConfigShim.cs
    ShimApiClasses/MinibatchSourceShim.cs
    ShimApiClasses/NDArrayViewShim.cs
    ShimApiClasses/NDMaskShim.cs
    ShimApiClasses/NDShapeShim.cs
    ShimApiClasses/ParameterShim.cs
    ShimApiClasses/StreamConfigurationShim.cs
    ShimApiClasses/TrainerShim.cs
    ShimApiClasses/ValueShim.cs
    ShimApiClasses/VariableShim.cs

    ../Swig/Generated/${CMAKE_HOST_SYSTEM_NAME}/${config}/AdditionalLearningOptions.cs
    ../Swig/Generated/${CMAKE_HOST_SYSTEM_NAME}/${config}/Axis.cs
    ../Swig/Generated/${CMAKE_HOST_SYSTEM_NAME}/${config}/AxisVector.cs
    ../Swig/Generated/${CMAKE_HOST_SYSTEM_NAME}/${config}/BoolVector.cs
    ../Swig/Generated/${CMAKE_HOST_SYSTEM_NAME}/${config}/CharVector.cs
    ../Swig/Generated/${CMAKE_HOST_SYSTEM_NAME}/${config}/CNTKDictionary.cs
    ../Swig/Generated/${CMAKE_HOST_SYSTEM_NAME}/${config}/CNTKLib.cs
    ../Swig/Generated/${CMAKE_HOST_SYSTEM_NAME}/${config}/CNTKLibPINVOKE.cs
    ../Swig/Generated/${CMAKE_HOST_SYSTEM_NAME}/${config}/Constant.cs
    ../Swig/Generated/${CMAKE_HOST_SYSTEM_NAME}/${config}/ConstantVector.cs
    ../Swig/Generated/${CMAKE_HOST_SYSTEM_NAME}/${config}/DataType.cs
    ../Swig/Generated/${CMAKE_HOST_SYSTEM_NAME}/${config}/DataUnit.cs
    ../Swig/Generated/${CMAKE_HOST_SYSTEM_NAME}/${config}/DeviceDescriptor.cs
    ../Swig/Generated/${CMAKE_HOST_SYSTEM_NAME}/${config}/DeviceDescriptorVector.cs
    ../Swig/Generated/${CMAKE_HOST_SYSTEM_NAME}/${config}/DeviceKind.cs
    ../Swig/Generated/${CMAKE_HOST_SYSTEM_NAME}/${config}/DictionaryValue.cs
    ../Swig/Generated/${CMAKE_HOST_SYSTEM_NAME}/${config}/DictionaryVector.cs
    ../Swig/Generated/${CMAKE_HOST_SYSTEM_NAME}/${config}/DoubleVector.cs
    ../Swig/Generated/${CMAKE_HOST_SYSTEM_NAME}/${config}/DoubleVectorVector.cs
    ../Swig/Generated/${CMAKE_HOST_SYSTEM_NAME}/${config}/Evaluator.cs
    ../Swig/Generated/${CMAKE_HOST_SYSTEM_NAME}/${config}/float16.cs
    ../Swig/Generated/${CMAKE_HOST_SYSTEM_NAME}/${config}/FloatVector.cs
    ../Swig/Generated/${CMAKE_HOST_SYSTEM_NAME}/${config}/FloatVectorVector.cs
    ../Swig/Generated/${CMAKE_HOST_SYSTEM_NAME}/${config}/Function.cs
    ../Swig/Generated/${CMAKE_HOST_SYSTEM_NAME}/${config}/FunctionPtrVector.cs
    ../Swig/Generated/${CMAKE_HOST_SYSTEM_NAME}/${config}/HTKFeatureConfiguration.cs
    ../Swig/Generated/${CMAKE_HOST_SYSTEM_NAME}/${config}/HTKFeatureConfigurationVector.cs
    ../Swig/Generated/${CMAKE_HOST_SYSTEM_NAME}/${config}/IntVector.cs
    ../Swig/Generated/${CMAKE_HOST_SYSTEM_NAME}/${config}/Learner.cs
    ../Swig/Generated/${CMAKE_HOST_SYSTEM_NAME}/${config}/LearnerVector.cs
    ../Swig/Generated/${CMAKE_HOST_SYSTEM_NAME}/${config}/MaskKind.cs
    ../Swig/Generated/${CMAKE_HOST_SYSTEM_NAME}/${config}/MinibatchData.cs
    ../Swig/Generated/${CMAKE_HOST_SYSTEM_NAME}/${config}/MinibatchInfo.cs
    ../Swig/Generated/${CMAKE_HOST_SYSTEM_NAME}/${config}/MinibatchSource.cs
    ../Swig/Generated/${CMAKE_HOST_SYSTEM_NAME}/${config}/MinibatchSourceConfig.cs
    ../Swig/Generated/${CMAKE_HOST_SYSTEM_NAME}/${config}/ModelFormat.cs
    ../Swig/Generated/${CMAKE_HOST_SYSTEM_NAME}/${config}/NDArrayView.cs
    ../Swig/Generated/${CMAKE_HOST_SYSTEM_NAME}/${config}/NDArrayViewPtrVector.cs
    ../Swig/Generated/${CMAKE_HOST_SYSTEM_NAME}/${config}/NDMask.cs
    ../Swig/Generated/${CMAKE_HOST_SYSTEM_NAME}/${config}/NDShape.cs
    ../Swig/Generated/${CMAKE_HOST_SYSTEM_NAME}/${config}/PaddingMode.cs
    ../Swig/Generated/${CMAKE_HOST_SYSTEM_NAME}/${config}/PairDoubleDouble.cs
    ../Swig/Generated/${CMAKE_HOST_SYSTEM_NAME}/${config}/PairFloatFloat.cs
    ../Swig/Generated/${CMAKE_HOST_SYSTEM_NAME}/${config}/PairIntInt.cs
    ../Swig/Generated/${CMAKE_HOST_SYSTEM_NAME}/${config}/PairNDArrayViewPtrNDArrayViewPtr.cs
    ../Swig/Generated/${CMAKE_HOST_SYSTEM_NAME}/${config}/PairSizeTDouble.cs
    ../Swig/Generated/${CMAKE_HOST_SYSTEM_NAME}/${config}/PairSizeTInt.cs
    ../Swig/Generated/${CMAKE_HOST_SYSTEM_NAME}/${config}/PairSizeTSizeT.cs
    ../Swig/Generated/${CMAKE_HOST_SYSTEM_NAME}/${config}/Parameter.cs
    ../Swig/Generated/${CMAKE_HOST_SYSTEM_NAME}/${config}/ParameterCloningMethod.cs
    ../Swig/Generated/${CMAKE_HOST_SYSTEM_NAME}/${config}/ParameterVector.cs
    ../Swig/Generated/${CMAKE_HOST_SYSTEM_NAME}/${config}/PoolingType.cs
    ../Swig/Generated/${CMAKE_HOST_SYSTEM_NAME}/${config}/ProgressWriter.cs
    ../Swig/Generated/${CMAKE_HOST_SYSTEM_NAME}/${config}/ProgressWriterVector.cs
    ../Swig/Generated/${CMAKE_HOST_SYSTEM_NAME}/${config}/SizeTVector.cs
    ../Swig/Generated/${CMAKE_HOST_SYSTEM_NAME}/${config}/SizeTVectorVector.cs
    ../Swig/Generated/${CMAKE_HOST_SYSTEM_NAME}/${config}/StorageFormat.cs
    ../Swig/Generated/${CMAKE_HOST_SYSTEM_NAME}/${config}/StreamConfiguration.cs
    ../Swig/Generated/${CMAKE_HOST_SYSTEM_NAME}/${config}/StreamConfigurationVector.cs
    ../Swig/Generated/${CMAKE_HOST_SYSTEM_NAME}/${config}/StreamInformation.cs
    ../Swig/Generated/${CMAKE_HOST_SYSTEM_NAME}/${config}/StringVector.cs
    ../Swig/Generated/${CMAKE_HOST_SYSTEM_NAME}/${config}/SWIGTYPE_p_int8_t.cs
    ../Swig/Generated/${CMAKE_HOST_SYSTEM_NAME}/${config}/SWIGTYPE_p_void.cs
    ../Swig/Generated/${CMAKE_HOST_SYSTEM_NAME}/${config}/TraceLevel.cs
    ../Swig/Generated/${CMAKE_HOST_SYSTEM_NAME}/${config}/Trainer.cs
    ../Swig/Generated/${CMAKE_HOST_SYSTEM_NAME}/${config}/TrainingParameterScheduleDouble.cs
    ../Swig/Generated/${CMAKE_HOST_SYSTEM_NAME}/${config}/UnorderedMapParameterNDArrayViewPtr.cs
    ../Swig/Generated/${CMAKE_HOST_SYSTEM_NAME}/${config}/UnorderedMapStreamInformationMinibatchData.cs
    ../Swig/Generated/${CMAKE_HOST_SYSTEM_NAME}/${config}/UnorderedMapStreamInformationPairNDArrayViewPtrNDArrayViewPtr.cs
    ../Swig/Generated/${CMAKE_HOST_SYSTEM_NAME}/${config}/UnorderedMapStringDictionaryValue.cs
    ../Swig/Generated/${CMAKE_HOST_SYSTEM_NAME}/${config}/UnorderedMapVariableMinibatchData.cs
    ../Swig/Generated/${CMAKE_HOST_SYSTEM_NAME}/${config}/UnorderedMapVariableValuePtr.cs
    ../Swig/Generated/${CMAKE_HOST_SYSTEM_NAME}/${config}/UnorderedMapVariableVariable.cs
    ../Swig/Generated/${CMAKE_HOST_SYSTEM_NAME}/${config}/UnsignedCharVector.cs
    ../Swig/Generated/${CMAKE_HOST_SYSTEM_NAME}/${config}/Value.cs
    ../Swig/Generated/${CMAKE_HOST_SYSTEM_NAME}/${config}/Variable.cs
    ../Swig/Generated/${CMAKE_HOST_SYSTEM_NAME}/${config}/VariableKind.cs
    ../Swig/Generated/${CMAKE_HOST_SYSTEM_NAME}/${config}/VariablePair.cs
    ../Swig/Generated/${CMAKE_HOST_SYSTEM_NAME}/${config}/VariablePairVector.cs
    ../Swig/Generated/${CMAKE_HOST_SYSTEM_NAME}/${config}/VariableVector.cs
    ../Swig/Generated/${CMAKE_HOST_SYSTEM_NAME}/${config}/VectorPairSizeTDouble.cs
)

ADD_SUBDIRECTORY(../Swig CSharpBindings)

add_custom_target(
    CNTKLibraryManagedDll ALL
    
    DEPENDS
        CSharpBindings
    
    SOURCES
        ${source_filenames}
        
    COMMAND dotnet build ${CMAKE_CURRENT_SOURCE_DIR}/CNTKLibraryManagedDll.csproj /p:OutputPathPrefix=${CMAKE_CURRENT_BINARY_DIR} /p:Configuration=${config} /t:Restore
    COMMAND dotnet build ${CMAKE_CURRENT_SOURCE_DIR}/CNTKLibraryManagedDll.csproj /p:OutputPathPrefix=${CMAKE_CURRENT_BINARY_DIR} /p:Configuration=${config} /t:Build
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_BINARY_DIR}/CSharpBindings/Cntk.Core.CSBinding${binary_name_suffix}${CMAKE_SHARED_LIBRARY_SUFFIX} ${CMAKE_CURRENT_BINARY_DIR}/AnyCPU/${config}
)

add_dependencies(CNTKLibraryManagedDll CSharpBindings)
