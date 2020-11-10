#pragma once

#include <array>
#include <string>
#include <vector>

#include "../nSkinz/item_definitions.hpp"

enum class FrameStage;
class GameEvent;

namespace SkinChanger
{
    void initializeKits() noexcept;
    void run(FrameStage) noexcept;
    void scheduleHudUpdate() noexcept;
    void overrideHudIcon(GameEvent& event) noexcept;
    void updateStatTrak(GameEvent& event) noexcept;

    struct PaintKit {
        PaintKit(int id, const std::string& name, const std::wstring& nameUpperCase) noexcept : id(id), name(name), nameUpperCase(nameUpperCase) { }
        int id;
        std::string name;
        std::wstring nameUpperCase;

        auto operator<(const PaintKit& other) const noexcept
        {
            return nameUpperCase < other.nameUpperCase;
        }
    };

    const std::vector<PaintKit>& getSkinKits() noexcept;
    const std::vector<PaintKit>& getGloveKits() noexcept;
    const std::vector<PaintKit>& getStickerKits() noexcept;
}

struct sticker_setting
{
	void update()
	{
		kit = SkinChanger::getStickerKits()[kit_vector_index].id;
	}


	auto operator==(const sticker_setting& o) const
	{
		return kit == o.kit
			&& kit_vector_index == o.kit_vector_index
			&& wear == o.wear
			&& scale == o.scale
			&& rotation == o.rotation;
	}

	int kit = 0;
	int kit_vector_index = 0;
	float wear = (std::numeric_limits<float>::min)();
	float scale = 1.f;
	float rotation = 0.f;
};

struct item_setting
{
	void update()
	{
		itemId = game_data::weapon_names[itemIdIndex].definition_index;
		quality = game_data::quality_names[entity_quality_vector_index].index;

		const std::vector<SkinChanger::PaintKit>* kit_names;
		const game_data::weapon_name* defindex_names;

		if (itemId == GLOVE_T_SIDE)
		{
			kit_names = &SkinChanger::getGloveKits();
			defindex_names = game_data::glove_names;
		} else
		{
			kit_names = &SkinChanger::getSkinKits();
			defindex_names = game_data::knife_names;
		}

		paintKit = (*kit_names)[paint_kit_vector_index].id;
		definition_override_index = defindex_names[definition_override_vector_index].definition_index;

		for (auto& sticker : stickers)
			sticker.update();
	}

	bool enabled = false;
	int itemIdIndex = 0;
	int itemId = 1;
	int entity_quality_vector_index = 0;
	int quality = 0;
	int paint_kit_vector_index = 0;
	int paintKit = 0;
	int definition_override_vector_index = 0;
	int definition_override_index = 0;
	int seed = 0;
	int stat_trak = -1;
	float wear = (std::numeric_limits<float>::min)();
	char custom_name[32] = "";
	std::array<sticker_setting, 5> stickers;
};

item_setting* get_by_definition_index(int definition_index);