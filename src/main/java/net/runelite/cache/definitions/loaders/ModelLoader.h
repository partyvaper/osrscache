#pragma once

#include "../ModelDefinition.h"
#include "../../io/InputStream.h"
#include <vector>
#include <memory>

namespace net::runelite::cache::definitions::loaders
{

	using ModelDefinition = net::runelite::cache::definitions::ModelDefinition;

	class ModelLoader : public std::enable_shared_from_this<ModelLoader>
	{
	public:
		virtual std::shared_ptr<ModelDefinition> load(int modelId, std::vector<signed char> &b);

		virtual void decodeType3(std::shared_ptr<ModelDefinition> def, std::vector<signed char> &var1);

		virtual void decodeType2(std::shared_ptr<ModelDefinition> def, std::vector<signed char> &var1);

		virtual void decodeType1(std::shared_ptr<ModelDefinition> def, std::vector<signed char> &var1);

		virtual void decodeOldFormat(std::shared_ptr<ModelDefinition> def, std::vector<signed char> &inputData);

	};

}
