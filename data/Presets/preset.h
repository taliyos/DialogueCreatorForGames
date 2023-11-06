#ifndef PRESET_H
#define PRESET_H

#include "data/Fields/fielddata.h"
#include "data/Fields/fieldtypes.h"
#include "widgets/editor/MainEditor/maineditor.h"
#include <QObject>

/**
 * The Preset class holds field data. it does not retain any text or effect information
 * stored within the original data.
 */
class Preset
{
public:
    Preset(FieldData* data);

    /**
     * Stores the provided data as this class's preset.
     * @param data - the structure to use as a skeleton.
     */
    void createPreset(FieldData* data);

    /**
     * Applies the saved structure to the end of the data. All existing data is maintained.
     * @param data - the main designer structure.
     */
    void apply(FieldData* data, MainEditor* editor);

    QString getDescription() const;

private:
    std::vector<FieldTypes> storage = std::vector<FieldTypes>();
    QString description = QString();
};

#endif // PRESET_H
