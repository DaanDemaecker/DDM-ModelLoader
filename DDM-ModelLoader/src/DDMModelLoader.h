// DDMModelLoader.h

// This class will be the main object that will allow the user to load in models
// It will serve


#ifndef DDMModelLoaderIncluded
#define DDMModelLoaderIncluded

namespace DDM
{
	class ModelLoader final
	{
	public:
		// Default constructor
		ModelLoader();
		
		// Default destructor
		~ModelLoader() = default;

		// Delete copy- and move operations
		ModelLoader(ModelLoader& other) = delete;
		ModelLoader(ModelLoader&& other) = delete;

		ModelLoader& operator=(ModelLoader& other) = delete;
		ModelLoader& operator=(ModelLoader&& other) = delete;

	private:


	};
}


#endif // !DDMModelLoaderIncluded
