//THIS IS 4_World SCRIP!!!!!!!

modded class PlayerBase   //modding a player base class since we will work with character
{
    bool z_hassuit;     //some shitass bools

    bool HasSuit()
    {
        return z_hassuit;
    }

    void SetHasSuit(bool state)
    {
        z_hassuit = state;
    }

    void HideALLStuff(bool state)
    {
        HideBodyParts(state);
        HideOtherStuff(state);
    }

    void HideBodyParts(bool state)  // void to hide body parts (usefull if your item clipping with character body parts)
    {   
        EntityAI bodypart;
        int slot_id;
        
        int decaySec = GetHiddenSelectionIndex("decay_preload"); // decay preload to make things right
        SetObjectTexture(decaySec, ""); // apply a transparent texture to character body part or items in particular slot

        array<string> bodyparts = {""};         //you can write here body parts which you need to hide if your item clip thru ("Gloves","Body","Legs","Feet","Head","Hips","pelvis","leftleg","rightleg")
                
        for ( int i = 0; i < bodyparts.Count(); i++ )
        {
            slot_id = InventorySlots.GetSlotIdFromString(bodyparts.Get(i));
            bodypart = GetInventory().FindPlaceholderForSlot(slot_id); // some functions and shitass calculations 
            
            if ( bodypart )
            {
                bodypart.SetInvisible(state); //set state invisible
            }
        }           
    }

    void HideOtherStuff(bool state)
{
    array<EntityAI> items = {};
    GetInventory().EnumerateInventory(InventoryTraversalType.PREORDER, items);

    for (int i = 0; i < items.Count(); i++)
    {
        EntityAI z_items = EntityAI.Cast(items[i]);

        bool IsPantsAttachment = false; //dont pay attention to such foolish bool namings,35% of the code made by chatgpt

        // Check if the item is in the Legs character attachments slot,it has consequences - area between your item and boots (socks area) will be transparent,
        //not really visible from FPP and TPP unless you play in 4K or fall prone a lot of times. Other solution is to wear high boots or make your item model cover this area.--/
        if (z_items.GetInventory().GetSlotId(0) == InventorySlots.GetSlotIdFromString("Legs")) // <------------------------------------------------------------------------------
        {
            IsPantsAttachment = true;
        }

        // Check if the player is wearing the suit, if so, hide only items in the pants attachments slot
        if (HasSuit())
        {
            if (IsPantsAttachment)
            {
                z_items.SetInvisible(state);
            }
        }
        else // If the player is not wearing the suit, show all items by setting invisible state false
        {
            z_items.SetInvisible(false);
        }
    }
}

    override void EOnFrame(IEntity other, float timeSlice) // some serious eonframe shit
    {
        super.EOnFrame(other, timeSlice);
        EntityAI suit;
        findSuit(this, suit);
        
        zfUnicorn_Kiga_Base new_suit = zfUnicorn_Kiga_Base.Cast(suit); // not tested do you need to replace this with your item base class or not,let me know.
        if (suit)
        {
            HideALLStuff(true);
            SetHasSuit(true);
        }
        if (!suit)
        {
            HideALLStuff(false);
            SetHasSuit(false);
        }
    }

    void findSuit(PlayerBase player, out EntityAI suit = NULL)
    {
        int z_slot_id = InventorySlots.GetSlotIdFromString("Body"); // slot which your item occupy
        ItemBase z_item = ItemBase.Cast(player.GetInventory().FindAttachment(z_slot_id));
        if(z_item)
        {
            if(z_item.IsKindOf("zfUnicorn_Kiga_Base")) // your item base class 
            {
                suit = z_item;
            }
        }
    }
};
