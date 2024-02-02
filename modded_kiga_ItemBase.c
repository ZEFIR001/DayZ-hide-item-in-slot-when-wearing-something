//THIS IS 4_World SCRIPT!!!!!

modded class ItemBase
{
	//to prevent dropped items being invisible if player drops item while wearing suit.
	void OnInventoryExit(Man player) //Void on inventory exit
	{
		PlayerBase z_player = PlayerBase.Cast(player); //assign to character
		if(z_player.HasSuit())  //checks if character has a suit
		{
			SetInvisible(false); //set invisible function
		}
		super.OnInventoryExit(player); //act with high priority on inventory closing
	}
}