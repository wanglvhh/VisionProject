/***********************************************************
 * File generated by the HALCON-Compiler hcomp version 17.12
 * Usage: Interface to C++
 *
 * Software by: MVTec Software GmbH, www.mvtec.com
 ***********************************************************/


#ifndef HCPP_HDLCLASSIFIERTRAINRESULT
#define HCPP_HDLCLASSIFIERTRAINRESULT

namespace HalconCpp
{

// Represents an instance of a Deep Neural Network training step result.
class LIntExport HDlClassifierTrainResult : public HToolBase
{

public:

  // Create an uninitialized instance
  HDlClassifierTrainResult():HToolBase() {}

  // Copy constructor
  HDlClassifierTrainResult(const HDlClassifierTrainResult& source) : HToolBase(source) {}

  // Create HDlClassifierTrainResult from handle, taking ownership
  explicit HDlClassifierTrainResult(Hlong handle);

  // Set new handle, taking ownership
  void SetHandle(Hlong handle);



/*****************************************************************************
 * Operator-based class constructors
 *****************************************************************************/

  // train_dl_classifier_batch: Perform a training step of a deep-learning-based classifier on a batch of  images.
  explicit HDlClassifierTrainResult(const HImage& BatchImages, const HDlClassifier& DLClassifierHandle, const HTuple& BatchLabels);




  /***************************************************************************
   * Operators                                                               *
   ***************************************************************************/

  // Return the results for the single training step of a deep-learning-based  classifier.
  HTuple GetDlClassifierTrainResult(const HTuple& GenParamName) const;

  // Return the results for the single training step of a deep-learning-based  classifier.
  HTuple GetDlClassifierTrainResult(const HString& GenParamName) const;

  // Return the results for the single training step of a deep-learning-based  classifier.
  HTuple GetDlClassifierTrainResult(const char* GenParamName) const;

  // Perform a training step of a deep-learning-based classifier on a batch of  images.
  void TrainDlClassifierBatch(const HImage& BatchImages, const HDlClassifier& DLClassifierHandle, const HTuple& BatchLabels);

};

// forward declarations and types for internal array implementation

template<class T> class HSmartPtr;
template<class T> class HToolArrayRef;

typedef HToolArrayRef<HDlClassifierTrainResult> HDlClassifierTrainResultArrayRef;
typedef HSmartPtr< HDlClassifierTrainResultArrayRef > HDlClassifierTrainResultArrayPtr;


// Represents multiple tool instances
class LIntExport HDlClassifierTrainResultArray : public HToolArray
{

public:

  // Create empty array
  HDlClassifierTrainResultArray();

  // Create array from native array of tool instances
  HDlClassifierTrainResultArray(HDlClassifierTrainResult* classes, Hlong length);

  // Copy constructor
  HDlClassifierTrainResultArray(const HDlClassifierTrainResultArray &tool_array);

  // Destructor
  virtual ~HDlClassifierTrainResultArray();

  // Assignment operator
  HDlClassifierTrainResultArray &operator=(const HDlClassifierTrainResultArray &tool_array);

  // Clears array and all tool instances
  virtual void Clear();

  // Get array of native tool instances
  const HDlClassifierTrainResult* Tools() const;

  // Get number of tools
  virtual Hlong Length() const;

  // Create tool array from tuple of handles
  virtual void SetFromTuple(const HTuple& handles);

  // Get tuple of handles for tool array
  virtual HTuple ConvertToTuple() const;

protected:

// Smart pointer to internal data container
   HDlClassifierTrainResultArrayPtr *mArrayPtr;
};

}

#endif
