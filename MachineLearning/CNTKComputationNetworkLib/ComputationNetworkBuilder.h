// ComputationNetworkBuilder -- helper class for constructing ComputationNetworks and ComputationNodes from C++ (internal and external)

#pragma once

#include "Basics.h"
#include "ComputationNode.h"
#include "ComputationNetwork.h"
#include "TrainingCriterionNodes.h" // for NCEEvalMode
#include <string>

namespace Microsoft { namespace MSR { namespace CNTK {

    template<class ElemType>
    class ComputationNetworkBuilder
    {
        typedef shared_ptr<ComputationNode<ElemType>> ComputationNodePtr;
        ComputationNetwork & net;
        ComputationNetworkBuilder();
        ComputationNetworkBuilder(const ComputationNetworkBuilder&);
        void operator=(const ComputationNetworkBuilder&);
    public:
        ComputationNetworkBuilder(ComputationNetwork & net) : net(net) {}

        // -----------------------------------------------------------------------
        // node creation
        // -----------------------------------------------------------------------

        static ComputationNodePtr NewStandardNode(const std::wstring & nodeType, DEVICEID_TYPE deviceId, const wstring & name);
        static ComputationNodePtr NewNode(const std::wstring & nodeType, DEVICEID_TYPE deviceId, const wstring & name);

        // The following functions create nodes and add them to the net, but don't attach inputs (some don't have inputs).
        // There are special versions for nodes with custom constructors, and a catch-all, CreateComputationNode(), for all others.
        // TODO: Do we really need these? Folks who want to use C++ can instead say net->AddNodeToNet(New<>(...)), which is not that different.
        // TODO: separate into nodes that have inputs and those that duplicate functions with input adding except just not adding inputs. Clear?

        ComputationNodePtr CreateLearnableParameter(const std::wstring & paramName, const size_t rows, const size_t cols);
        //sparse matrix size is optionally specified
        ComputationNodePtr CreateSparseLearnableParameter(const std::wstring & paramName, const size_t rows, const size_t cols, const size_t size = 0);
        ComputationNodePtr CreateInputNode(const std::wstring & inputName, const size_t rows, const size_t cols);
        ComputationNodePtr CreateSparseInputNode(const std::wstring & inputName, const size_t rows, const size_t cols);
        ComputationNodePtr CreateInputNode(const std::wstring & inputName, const ImageLayout & imageLayout, const size_t numImages);
        ComputationNodePtr CreateSparseInputNode(const std::wstring & inputName, const ImageLayout & imageLayout, const size_t numImages);
        ComputationNodePtr CreatePairNetworkNode(const std::wstring & inputName, const size_t rows, const size_t cols);
        ComputationNodePtr CreateConvolutionNode(const std::wstring & nodeName, const size_t kernelWidth, const size_t kernelHeight, const size_t outputChannels, const size_t horizontalSubsample, const size_t verticalSubsample, const bool zeroPadding = false, const size_t maxTempMemSizeInSamples = 0);
        ComputationNodePtr CreateMaxPoolingNode(const std::wstring & nodeName, const size_t windowWidth, const size_t windowHeight, const size_t horizontalSubsample, const size_t verticalSubsample);
        ComputationNodePtr CreateAveragePoolingNode(const std::wstring & nodeName, const size_t windowWidth, const size_t windowHeight, const size_t horizontalSubsample, const size_t verticalSubsample);
        // this is the catch-all for all cases not covered as special cases above
        // Unlike the specialized ones above, this one creates nodes by type given as a string.
        ComputationNodePtr CreateComputationNode(const std::wstring & nodeType, const std::wstring & nodeName);
        // TODO: These next three functions are wrappers around CreateXXXNode(). Remove these.
        ComputationNodePtr Parameter(const size_t rows, size_t cols, const std::wstring nodeName = L"") { return CreateLearnableParameter(nodeName, rows, cols); } // TODO: remove
        ComputationNodePtr Input(const size_t rows, const size_t cols, const std::wstring nodeName = L"") { return CreateInputNode(nodeName, rows, cols); } // TODO: remove
        ComputationNodePtr Input(const ImageLayout & imageLayout, const size_t numImages, const std::wstring nodeName = L"") { return CreateInputNode(nodeName, imageLayout, numImages); } // TODO: remove
        // The following functions create nodes and link them to the network and their inputs.
        // TODO: Do we need both this set and the one above that does not add inputs? Can they share more code?
        ComputationNodePtr PairNetwork(const ComputationNodePtr & a, const std::wstring nodeName = L"");
        ComputationNodePtr Convolution(const ComputationNodePtr weight,
            const ComputationNodePtr inputValues,
            const size_t kernelWidth,
            const size_t kernelHeight,
            const size_t outputChannels,
            const size_t horizontalSubsample,
            const size_t verticalSubsample,
            const bool zeroPadding = false,
            const std::wstring nodeName = L"",
            const size_t maxTempMemSizeInSamples = 0);
        ComputationNodePtr MaxPooling(const ComputationNodePtr inputValues,
            const size_t windowWidth,
            const size_t windowHeight,
            const size_t horizontalSubsample,
            const size_t verticalSubsample,
            const std::wstring nodeName = L"");
        ComputationNodePtr AveragePooling(const ComputationNodePtr inputValues,
            const size_t windowWidth,
            const size_t windowHeight,
            const size_t horizontalSubsample,
            const size_t verticalSubsample,
            const std::wstring nodeName = L"");
        ComputationNodePtr ErrorPrediction(const ComputationNodePtr a, const ComputationNodePtr b, const std::wstring nodeName = L"");
        ComputationNodePtr PerDimMeanVarNormalization(const ComputationNodePtr feature, const ComputationNodePtr mean, const ComputationNodePtr InvStdDev, const std::wstring nodeName = L"");
        ComputationNodePtr PerDimMeanVarDeNormalization(const ComputationNodePtr feature, const ComputationNodePtr mean, const ComputationNodePtr InvStdDev, const std::wstring nodeName = L"");
        ComputationNodePtr SquareError(const ComputationNodePtr a, const ComputationNodePtr b, const std::wstring nodeName = L"");
        ComputationNodePtr SequenceDecoder(const ComputationNodePtr label, const ComputationNodePtr prediction, const ComputationNodePtr pairscore, const std::wstring nodeName = L"");
        ComputationNodePtr CrossEntropyWithSoftmax(const ComputationNodePtr label, const ComputationNodePtr prediction, const std::wstring nodeName = L"");
        ComputationNodePtr SequenceWithSoftmax(const ComputationNodePtr label, const ComputationNodePtr prediction, const ComputationNodePtr loglikelihood, const std::wstring nodeName = L"");
        ComputationNodePtr NoiseContrastiveEstimation(const ComputationNodePtr label, const ComputationNodePtr prediction, const ComputationNodePtr input_weight, const ComputationNodePtr input_bias, const std::wstring nodeName = L"", NCEEvalMode mode = NCEEvalMode::None);
        ComputationNodePtr ClassCrossEntropyWithSoftmax(const ComputationNodePtr label, const ComputationNodePtr prediction, const ComputationNodePtr input_weight, const ComputationNodePtr cls_log_post_prob, const std::wstring nodeName = L"");
        ComputationNodePtr CRF(const ComputationNodePtr label, const ComputationNodePtr postDepScore, const ComputationNodePtr transition_score, const std::wstring nodeName = L"");
        ComputationNodePtr DummyCriterion(const ComputationNodePtr objectives, const ComputationNodePtr derivatives, const ComputationNodePtr prediction, const std::wstring nodeName = L"");
        ComputationNodePtr LSTM(const ComputationNodePtr obs, const ComputationNodePtr inputGate, const ComputationNodePtr forgetGate, const ComputationNodePtr outputGate, const ComputationNodePtr memoryCellWgt, const std::wstring nodeName = L"");
        ComputationNodePtr CrossEntropy(const ComputationNodePtr label, const ComputationNodePtr prediction, const std::wstring nodeName = L"");
        ComputationNodePtr MatrixL1Reg(const ComputationNodePtr a, const std::wstring nodeName = L"");
        ComputationNodePtr MatrixL2Reg(const ComputationNodePtr a, const std::wstring nodeName = L"");
        ComputationNodePtr Mean(const ComputationNodePtr a, const std::wstring nodeName = L"");
        ComputationNodePtr InvStdDev(const ComputationNodePtr a, const std::wstring nodeName = L"");
        ComputationNodePtr Negate(const ComputationNodePtr a, const std::wstring nodeName = L"");
        ComputationNodePtr RectifiedLinear(const ComputationNodePtr a, const std::wstring nodeName = L"");
        ComputationNodePtr Sigmoid(const ComputationNodePtr a, const std::wstring nodeName = L"");
        ComputationNodePtr Tanh(const ComputationNodePtr a, const std::wstring nodeName = L"");
        ComputationNodePtr Exp(const ComputationNodePtr a, const std::wstring nodeName = L"");
        ComputationNodePtr Log(const ComputationNodePtr a, const std::wstring nodeName = L"");
        ComputationNodePtr Cos(const ComputationNodePtr a, const std::wstring nodeName = L"");
        ComputationNodePtr Softmax(const ComputationNodePtr a, const std::wstring nodeName = L"");
        ComputationNodePtr LogSoftmax(const ComputationNodePtr a, const std::wstring nodeName = L"");
        ComputationNodePtr Sum(const ComputationNodePtr a, const std::wstring nodeName = L"");
        ComputationNodePtr Scale(const ComputationNodePtr scalar, const ComputationNodePtr matrix, const std::wstring nodeName = L"");
        ComputationNodePtr Transpose(const ComputationNodePtr matrix, const std::wstring nodeName = L"");
        ComputationNodePtr Times(const ComputationNodePtr a, const ComputationNodePtr b, const std::wstring nodeName = L"");
        ComputationNodePtr TransposeTimes(const ComputationNodePtr a, const ComputationNodePtr b, const std::wstring nodeName = L"");
        ComputationNodePtr ElementTimes(const ComputationNodePtr a, const ComputationNodePtr b, const std::wstring nodeName = L"");
        ComputationNodePtr RowElementTimes(const ComputationNodePtr a, const ComputationNodePtr b, const std::wstring nodeName = L"");
        ComputationNodePtr ColumnElementTimes(const ComputationNodePtr a, const ComputationNodePtr b, const std::wstring nodeName = L"");
        ComputationNodePtr StrideTimes(const ComputationNodePtr a, const ComputationNodePtr b, const ComputationNodePtr c, const std::wstring nodeName = L"");
        ComputationNodePtr DiagTimes(const ComputationNodePtr a, const ComputationNodePtr b, const std::wstring nodeName = L"");
        ComputationNodePtr CosDistance(const ComputationNodePtr a, const ComputationNodePtr b, const std::wstring nodeName = L"");
        ComputationNodePtr KhatriRaoProduct(const ComputationNodePtr a, const ComputationNodePtr b, const std::wstring nodeName = L"");
        ComputationNodePtr Plus(const ComputationNodePtr a, const ComputationNodePtr b, const std::wstring nodeName = L"");
        ComputationNodePtr Minus(const ComputationNodePtr a, const ComputationNodePtr b, const std::wstring nodeName = L"");
        ComputationNodePtr Dropout(const ComputationNodePtr a, const std::wstring nodeName = L"");
        ComputationNodePtr Reshape(const ComputationNodePtr a, const size_t num_rows, const ImageLayout & imageLayout, const std::wstring nodeName = L"");
        ComputationNodePtr RowRepeat(const ComputationNodePtr a, const size_t num_repeat, const std::wstring nodeName = L"");
        ComputationNodePtr Diagonal(const ComputationNodePtr a, const std::wstring nodeName = L"");
        ComputationNodePtr PastValue(const ComputationNodePtr a, const float initHiddenActivity, const size_t row_size, const size_t col_size, size_t timeStep, const std::wstring nodeName = L"");
        ComputationNodePtr FutureValue(const ComputationNodePtr a, const float initHiddenActivity, const size_t row_size, const size_t col_size, size_t timeStep, const std::wstring nodeName = L"");
        ComputationNodePtr Parallel(const ComputationNodePtr a, const ComputationNodePtr b, const std::wstring nodeName = L"");
        ComputationNodePtr RowSlice(const ComputationNodePtr a, const size_t start_index, const size_t num_rows, const std::wstring nodeName = L"");
        ComputationNodePtr RowStack(const std::vector<ComputationNodePtr> pinputs, const std::wstring nodeName = L"");
        ComputationNodePtr GMMLogLikelihood(const ComputationNodePtr unnormedPrior, const ComputationNodePtr mean, const ComputationNodePtr logStddev, const ComputationNodePtr feature, const std::wstring nodeName = L"");
        ComputationNodePtr TimeReverse(const ComputationNodePtr input, const std::wstring nodeName = L"");
        ComputationNodePtr LookupTable(const ComputationNodePtr dictionary, const ComputationNodePtr input, const std::wstring nodeName = L"");
    };

}}}
