// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/GridPanel.h"
#include "InventorySystem/Item/BasicItemDataAsset.h"
#include "SingleSlotObj.generated.h"


class USlateBrushAsset;
class UDynamicInventoryGrid;
class UInventoryItemDisplay;
class UBorder;
/**
 *
 */
UCLASS()
class INVENTORYSYSTEM_API USingleSlotObj : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void SetCoordinate(const int RowNo, const int ColumnNo);

	UPROPERTY(EditDefaultsOnly)
		USlateBrushAsset* BrushAsset = nullptr;

	UPROPERTY(EditDefaultsOnly)
		FLinearColor ValidPlaceColor;

	UPROPERTY(EditDefaultsOnly)
		FLinearColor InvalidPlaceColor;

	UPROPERTY(EditAnywhere, Category = "Size Settings")
		float WidgetWidth;
	UPROPERTY(EditAnywhere, Category = "Size Settings")
		float WidgetHeight;
	//the single slot object has no owner this will be handled differently.
	UPROPERTY()
		UDynamicInventoryGrid* Owner = nullptr;

	UFUNCTION(BlueprintCallable)
	bool AddItem(UBasicItemDataAsset* ItemDataAsset);

	void SetIndex(const int Index) { SlotIndex = Index; };

	void EnableFillorReFill(const bool IsFill);

	bool AddItemAtIndex(UBasicItemDataAsset* ItemDataAsset, int Index);

	void FillSlots(const FIntPoint& StartPoint, const FIntPoint& ItemSize);

	FIntPoint GetCoordinateByIndex(const int Index) const;

	UPROPERTY(meta = (BindWidget))
		UBorder* Border = nullptr;

	int GetIndex() const { return SlotIndex; }

	TMap<int32, UInventoryItemDisplay*> ItemDisplayContainer;

	//UPROPERTY(EditAnywhere, meta = (BindWidget))
		//UGridPanel* InventoryGridPanel = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Class Settings")
		TSubclassOf<UInventoryItemDisplay> ItemDisplayClass;

private:

	bool bCanDraw = false;
	int SlotIndex = -1;
	int Row = -1;
	int Column = -1;

	FVector2D DrawSize = FVector2D::ZeroVector;

	FLinearColor Color;

	UFUNCTION(NetMulticast, reliable)
	void MoveItemOnServer(UDynamicInventoryGrid* GridPanel, int pIndex, int sIndex);

	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
	virtual bool NativeOnDragOver(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;

	virtual int32 NativePaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect,
	FSlateWindowElementList& OutDrawElements, int32 LayerId,
	const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;

	virtual void NativeOnDragLeave(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
	virtual void NativeOnDragCancelled(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
};
