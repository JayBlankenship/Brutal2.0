// Fill out your copyright notice in the Description page of Project Settings.


#include "SingleSlotObj.h"
#include "InventorySystem/ModdedALSCharacter.h"
#include "DragDropWidget.h"
#include "DynamicInventoryGrid.h"

#include "InventoryItemDisplay.h"
#include "Components/GridPanel.h"
#include "InventoryItemDisplay.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Components/GridSlot.h"
#include "Blueprint/UserWidget.h"
#include "Components/Border.h"

#include "InventorySystem/Item/BasicItemDataAsset.h"
#include "Rendering/DrawElements.h"

void USingleSlotObj::MoveItemOnServer_Implementation(UDynamicInventoryGrid* GridPanel, int pIndex, int sIndex)
{
	if (ROLE_Authority)
		//UE_LOG(LogTemp, Error, TEXT("if(ROLE_Authority)"),);
		//UE_LOG(LogTemp, Error, TEXT("UInventorySlot::MoveItemOnServer_Implementation()"), );
		if (GridPanel)
		{
			UE_LOG(LogTemp, Error, TEXT("if (GridPanel) = %s"), *GridPanel->GetName());
			UE_LOG(LogTemp, Error, TEXT("if (GridPanel) = %s"), *GridPanel->GetRootWidget()->GetName());
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("else GridPanel = null"), );
		}
	if (Owner)
	{
		//UE_LOG(LogTemp, Error, TEXT("if (pOwner) = %s"),*pOwner->GetName() );
		//UE_LOG(LogTemp, Error, TEXT("Owner = %s"), *Owner->GetName());
		UE_LOG(LogTemp, Error, TEXT("int pIndex =  %d"), pIndex);
		UE_LOG(LogTemp, Error, TEXT("int sIndex =  %d"), sIndex);
	}
	//pOwner->index
	//UInventoryItemDisplay* zItem =  *Owner->ItemDisplayContainer.Find(pIndex);

	UInventoryItemDisplay* zItem = Owner->ItemDisplayContainer.FindRef(pIndex);

	if (zItem)
	{
		//zItem->SetInventoryIndex(sIndex);
		UE_LOG(LogTemp, Error, TEXT("UInventoryItemDisplay* zItem =  *Owner->ItemDisplayContainer.Find(pIndex) %s"), *zItem->GetName());
		//zItem->

		//FIntPoint coord = Owner->GetCoordinateByIndex(pIndex);
		//FIntPoint ncoord = Owner->GetCoordinateByIndex(sIndex);
		//Owner->ClearSlots(coord, zItem->GetItemSize());
		//Owner->FillSlots(ncoord, zItem->GetItemSize());
		//Owner->RemoveItem(zItem->ItemData);
		//zItem->SetVisibility(ESlateVisibility::Hidden);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("zItem =  nullptr"), );
	}
	for (TPair<int32, UInventoryItemDisplay*> pItem : Owner->ItemDisplayContainer)
	{
		//pItem->GetName();
		UE_LOG(LogTemp, Error, TEXT("pItem =  %s"), *pItem.Value->GetName());
		UE_LOG(LogTemp, Error, TEXT(" pItem.Key =  %d"), pItem.Key);
		FIntPoint coord = Owner->GetCoordinateByIndex(pIndex);
		UE_LOG(LogTemp, Error, TEXT(" Owner->GetCoordinateByIndex(pIndex) =   %d"), pItem.Key);
	}

}

void USingleSlotObj::SetCoordinate(const int RowNo, const int ColumnNo)
{
	Row = RowNo;
	Column = ColumnNo;
}

void USingleSlotObj::EnableFillorReFill(const bool IsFill)
{
	if (IsFill)
	{
		Border->SetBrushColor(FLinearColor::Red);
	}
	else
	{
		Border->SetBrushColor(FLinearColor::Green);
	}
}

bool USingleSlotObj::AddItemAtIndex(UBasicItemDataAsset* ItemDataAsset, int Index)
{
	//const int Index = GetFirstAvailableSlotIndex(ItemDataAsset->GetItemSize());

	if (ItemDataAsset->IsStackable())
	{
		for (const auto ItemRef : ItemDisplayContainer)
		{
			if (ItemRef.Value->ItemData->GetId() == ItemDataAsset->GetId())
			{
				ItemRef.Value->ItemData->AddStack(ItemDataAsset->GetStackSize());
				ItemRef.Value->IncreaseCount();
				return true;
			}
		}
	}

	if (Index != -1)
	{
		UInventoryItemDisplay* InventoryItemDisplay = CreateWidget<UInventoryItemDisplay>(this, ItemDisplayClass);
		InventoryItemDisplay->Init(ItemDataAsset);
		InventoryItemDisplay->SetInventoryIndex(Index);
		//InventoryItemDisplay->Owner = this;

		const FIntPoint ItemStartPoint = GetCoordinateByIndex(Index);
		//single slot no grid
		//InventoryGridPanel->AddChildToGrid(InventoryItemDisplay, ItemStartPoint.Y, ItemStartPoint.X);
		
		ItemDisplayContainer.Add(Index, InventoryItemDisplay);

		FillSlots(ItemStartPoint, ItemDataAsset->GetItemSize());
		
		return true;
	}

	return false;
}
void USingleSlotObj::FillSlots(const FIntPoint& StartPoint, const FIntPoint& ItemSize)
{
	UE_LOG(LogTemp, Warning, TEXT(" StartPoint.X = %d , StartPoint.Y = %d"), StartPoint.X, StartPoint.Y);
	//int Index = (StartPoint.Y * ColumnCount) + StartPoint.X;
	//UE_LOG(LogTemp, Warning, TEXT("Jays Next Index %d"), Index);
	//UE_LOG(LogTemp, Warning, TEXT("Jays Next Index function %d"), Index + i + (j * (RowCount - 1)));
	for (int i = 0; i < ItemSize.X; i++)
	{
		for (int j = 0; j < ItemSize.Y; j++)
		{
			//UE_LOG(LogTemp, Warning, TEXT("Jays Next Index function %d"), Index + i + (j * (ColumnCount)));
			//UE_LOG(LogTemp, Warning, TEXT("GetSlotIndexByCoordinate((StartPoint.X + i) % ColumnCount, (StartPoint.Y + j) % RowCount) %d"), GetSlotIndexByCoordinate((StartPoint.X + i) % ColumnCount, (StartPoint.Y + j) % RowCount));
			//UE_LOG(LogTemp, Warning, TEXT("(StartPoint.X + i) % ColumnCount, (StartPoint.Y + j) % RowCount) =  (%d,%d)"), (StartPoint.X + i) % ColumnCount, (StartPoint.Y + j) % RowCount);

			//UE_LOG(LogTemp, Warning, TEXT("GetSlotIndexByCoordinate((StartPoint.X + i) % ColumnCount, (StartPoint.Y + j) % RowCount) == %i"), GetSlotIndexByCoordinate((StartPoint.X + i) % ColumnCount, (StartPoint.Y + j) % RowCount));
			//auto& SingleSlot = Slots[GetSlotIndexByCoordinate((StartPoint.X + i) % ColumnCount, (StartPoint.Y + j) % RowCount)];

			//auto& SingleSlot = Slots[Index + i + (j * (ColumnCount))];
			//SlotMap.Add(SingleSlot, true);
			// SingleSlot->EnableFillorReFill(true);
			//EnableFillorReFill(true);
		}
	}
}
FIntPoint USingleSlotObj::GetCoordinateByIndex(const int Index) const
{
	//if (Index >= 0 && Index < Slots.Num())
	//{
	//	if (UInventorySlot* InvSlot = Cast<UInventorySlot>(Slots[Index]))
	//	{
	//		if (UGridSlot* GridSlot = Cast<UGridSlot>(InvSlot->Slot))
	//		{
	//			return FIntPoint{ GridSlot->Column, GridSlot->Row };
	//		}
	//	}
	//}
	return FIntPoint{ 0,0 };
	//return FIntPoint{ -1,-1 };
}

bool USingleSlotObj::AddItem(UBasicItemDataAsset* ItemDataAsset)
{
	//todoneed to ADD
	//const int Index = GetFirstAvailableSlotIndex(ItemDataAsset->GetItemSize());//this is one slot so for now we'll just use 0. which is 1st
	const int Index = 0;

	//good question... is stackable? and then what ?
	if (ItemDataAsset->IsStackable())
	{
		for (const auto ItemRef : ItemDisplayContainer)
		{
			if (ItemRef.Value->ItemData->GetId() == ItemDataAsset->GetId())
			{
				ItemRef.Value->ItemData->AddStack(ItemDataAsset->GetStackSize());
				ItemRef.Value->IncreaseCount();
				return true;
			}
		}
	}
	//todoneed to ADD
	if (Index != -1)
	{
		UInventoryItemDisplay* InventoryItemDisplay = CreateWidget<UInventoryItemDisplay>(this, ItemDisplayClass);
		InventoryItemDisplay->Init(ItemDataAsset);
		InventoryItemDisplay->SetInventoryIndex(Index);
		//InventoryItemDisplay->Owner = this; the owner of this is now going to fill a different varable and ill have to handle it specifically on the side of the grid going back 

		const FIntPoint ItemStartPoint = GetCoordinateByIndex(Index);// itll get 0,0
		//InventoryGridPanel is null, we need to add our own addchildtogrid, will be called addchildtoslot, 
		// LOOKATTHIS
		//InventoryGridPanel->AddChildToGrid(InventoryItemDisplay, ItemStartPoint.Y, ItemStartPoint.X);
		//this is ok for now , basically we should not do anything if this is full.,,, that is not empty........ NOTE
		ItemDisplayContainer.Add(Index, InventoryItemDisplay);

		FillSlots(ItemStartPoint, ItemDataAsset->GetItemSize());

		return true;
	}

	return false;
}

bool USingleSlotObj::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent,
	UDragDropOperation* InOperation)
{
	Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);
	UDragDropWidget* DropWidget = Cast<UDragDropWidget>(InOperation);
	if (DropWidget->OriginalOwner != Owner)
	{
		UE_LOG(LogTemp, Warning, TEXT("Log on line 102 "));
		if (UInventoryItemDisplay* InventoryItemDisplay = Cast<UInventoryItemDisplay>(DropWidget->WidgetToDrag))
		{
			UE_LOG(LogTemp, Warning, TEXT("Log on line 103"));
			UE_LOG(LogTemp, Warning, TEXT("Log on InventoryItemDisplay = %s"), *FString(InventoryItemDisplay->GetName()));
			if (Owner)
			{
				UE_LOG(LogTemp, Warning, TEXT("Log on line 106"));
				if (Owner->IsItemAvailableForSlot(SlotIndex, InventoryItemDisplay->GetItemSize()))
				{
					bCanDraw = false;
					DropWidget->OriginalOwner->RemoveItematindex(DropWidget->Data, InventoryItemDisplay->GetInventoryIndex());
					DropWidget->OriginalOwner = Owner;
					Owner->AddItemAtIndex(DropWidget->Data, this->GetIndex());
					InventoryItemDisplay->GetInventoryIndex();
					InventoryItemDisplay->SetInventoryIndex(this->GetIndex());
					//MoveItemOnServer(Owner, InventoryItemDisplay->GetInventoryIndex(),this->GetIndex());
				}
				else
				{
					bCanDraw = false;
					return false;
				}
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("Owner is null, which is ok bc the owner would norm be a grid this slot is alone"));
				//so this is the instance that a drag and drop is being dragged to us a single slot inventory 
				if (ItemDisplayContainer.IsEmpty())
				{
					AddItem(InventoryItemDisplay->ItemData);
					return true;
				}
				else
				{
					return false;
				}
			}
		}
	}
	if (DropWidget->OriginalOwner != Owner)
	{
		//UE_LOG(LogTemp, Warning, TEXT("Log on line 99 "));
		if (UGridPanel* GridPanel = Cast<UGridPanel>(GetParent()))
		{
			//UE_LOG(LogTemp, Warning, TEXT("Log on line 102 "));
			if (UInventoryItemDisplay* InventoryItemDisplay = Cast<UInventoryItemDisplay>(DropWidget->WidgetToDrag))
			{
				//UE_LOG(LogTemp, Warning, TEXT("Log on line 103"));
				if (Owner)
				{
					//UE_LOG(LogTemp, Warning, TEXT("Log on line 106"));
					if (Owner->IsItemAvailableForSlot(SlotIndex, InventoryItemDisplay->GetItemSize()))
					{
						bCanDraw = false;
						DropWidget->OriginalOwner->RemoveItematindex(DropWidget->Data, InventoryItemDisplay->GetInventoryIndex());
						DropWidget->OriginalOwner = Owner;
						Owner->AddItemAtIndex(DropWidget->Data, this->GetIndex());
						InventoryItemDisplay->GetInventoryIndex();
						InventoryItemDisplay->SetInventoryIndex(this->GetIndex());
						//MoveItemOnServer(Owner, InventoryItemDisplay->GetInventoryIndex(),this->GetIndex());
					}
					else
					{
						bCanDraw = false;
						return false;
					}
				}
			}
		}
		return true;
	}

	if (DropWidget == nullptr)
	{
		// GEngine->AddOnScreenDebugMessage(-1,1.f, FColor::Black, "FALSE");
		return false;
	}

	// const FString Message = FString::Printf(TEXT("ROW [%d] COLUMN [%d]"), Row, Column);
	// GEngine->AddOnScreenDebugMessage(-1,1.f, FColor::Black, Message);

	if (UGridPanel* GridPanel = Cast<UGridPanel>(GetParent()))
	{
		UE_LOG(LogTemp, Warning, TEXT("Log on line 142"));
		if (DropWidget->OriginalOwner == Owner)
		{
			if (UInventoryItemDisplay* InventoryItemDisplay = Cast<UInventoryItemDisplay>(DropWidget->WidgetToDrag))
			{
				if (Owner)
				{
					if (Owner->IsItemAvailableForSlot(SlotIndex, InventoryItemDisplay->GetItemSize()))
					{
						InventoryItemDisplay->SetVisibility(ESlateVisibility::Visible);
						if (UGridSlot* GridSlot = Cast<UGridSlot>(InventoryItemDisplay->Slot))
						{
							GridSlot->SetColumn(Column);
							GridSlot->SetRow(Row);
						}
						UE_LOG(LogTemp, Error, TEXT("Owner = %s "), *Owner->GetName());
						MoveItemOnServer(Owner, InventoryItemDisplay->GetInventoryIndex(), this->GetIndex());
						Owner->GetOwningPlayer();
						UE_LOG(LogTemp, Error, TEXT("OwnerRIGHTBEFORE = %s "), *Owner->GetName());
						//Owner->GetOwningPlayerPawn()->GetName();
						UE_LOG(LogTemp, Error, TEXT("Owner->GetOwningPlayerPawn()->GetName() = %s "), *Owner->GetOwningPlayerPawn()->GetName());
						if (AModdedALSCharacter* myAModdedALSCharacter = Cast<AModdedALSCharacter>(Owner->GetOwningPlayerPawn()))
						{
							UE_LOG(LogTemp, Error, TEXT("Owner = %s "), *Owner->GetName());
							myAModdedALSCharacter->MoveItemOnServer(DropWidget->Data, Owner, InventoryItemDisplay->GetInventoryIndex(), this->GetIndex());
						}
						Owner->FillSlots(Owner->GetCoordinateByIndex(SlotIndex), InventoryItemDisplay->GetItemSize());
						InventoryItemDisplay->SetInventoryIndexAndChangeMap(this->GetIndex());
					}
					else
					{
						bCanDraw = false;
						return false;
					}
				}
			}
		}
	}

	bCanDraw = false;

	return true;
}

bool USingleSlotObj::NativeOnDragOver(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent,
	UDragDropOperation* InOperation)
{
	Super::NativeOnDragOver(InGeometry, InDragDropEvent, InOperation);
	if(Owner)
	UE_LOG(LogTemp, Warning, TEXT("OnDragOverOwner %s"), *Owner->GetName());

	//Owner;

	UDragDropWidget* DropWidget = Cast<UDragDropWidget>(InOperation);
	UE_LOG(LogTemp, Warning, TEXT("OnDragOverOriginalOwner %s"), *DropWidget->OriginalOwner->GetName());
	//DropWidget->
	//ADDED
	//EnableFillorReFill(true);
	//added
	bCanDraw = true;
	Color = ItemDisplayContainer.IsEmpty() ? ValidPlaceColor : InvalidPlaceColor;
	//UWidgetBlueprintLibrary::DrawBox(Context, { 0,0 }, DrawSize, BrushAsset, Color);
	if (DropWidget == nullptr)
	{
		return false;
	}
	
	if (Owner)// == DropWidget->OriginalOwner
	{
		if (UInventoryItemDisplay* InventoryItemDisplay = Cast<UInventoryItemDisplay>(DropWidget->WidgetToDrag))
		{
			const bool IsSlotValid = Owner->IsItemAvailableForSlot(SlotIndex, InventoryItemDisplay->GetItemSize());

			DrawSize = { FIntPoint(50) * InventoryItemDisplay->GetItemSize() };

			Color = IsSlotValid ? ValidPlaceColor : InvalidPlaceColor;
		}
		//Color = InvalidPlaceColor;
	}
	//if (InGeometry)
	//{

	//}
	if (UGridPanel* GridPanel = Cast<UGridPanel>(GetParent()))
	{
		// const FString Message = FString::Printf(TEXT("ROW [%d] COLUMN [%d]"), Row, Column);
		// GEngine->AddOnScreenDebugMessage(-1,1.f, FColor::Black, Message);

		bCanDraw = true;
	}

	return true;
}

int32 USingleSlotObj::NativePaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry,
	const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId,
	const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const
{
	Super::NativePaint(Args, AllottedGeometry, MyCullingRect, OutDrawElements, LayerId, InWidgetStyle, bParentEnabled);

	if (bCanDraw)
	{
		FPaintContext Context(AllottedGeometry, MyCullingRect, OutDrawElements, LayerId, InWidgetStyle, bParentEnabled);
		OnPaint(Context);

		//todo handle if box is out of Inventory widget
		//DrawSize = {FIntPoint(50)};// need to actually get the slots size of what we are filling 
		// Get the actual size and position of the widget on the screen
		FSlateRect WidgetRect = this->GetCachedGeometry().GetRenderBoundingRect();
		// Get the margin and padding values of the widget
		FMargin WidgetPadding = Cast<UUserWidget>(this)->Padding;
		float WidgetMarginLeft = WidgetPadding.Left;
		float WidgetMarginTop = WidgetPadding.Top;
		float WidgetMarginRight = WidgetPadding.Right;
		float WidgetMarginBottom = WidgetPadding.Bottom;

		// Adjust the widget size based on the margin and padding values
		//float WidgetWidth = WidgetRect.GetSize().X + WidgetMarginLeft + WidgetMarginRight;
		//float WidgetHeight = WidgetRect.GetSize().Y + WidgetMarginTop + WidgetMarginBottom;

		// Print the adjusted size of the widget
		UE_LOG(LogTemp, Log, TEXT("Widget adjusted size: %f x %f"), WidgetWidth, WidgetHeight);
		UWidgetBlueprintLibrary::DrawBox(Context, { 0,0 }, FIntPoint(WidgetWidth, WidgetHeight), BrushAsset, Color);
		UE_LOG(LogTemp, Warning, TEXT("painting  ") );
		return FMath::Max(LayerId, Context.MaxLayer);
	}

	return LayerId;
}

void USingleSlotObj::NativeOnDragLeave(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDragLeave(InDragDropEvent, InOperation);

	bCanDraw = false;
}

void USingleSlotObj::NativeOnDragCancelled(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDragCancelled(InDragDropEvent, InOperation);

	bCanDraw = false;
}