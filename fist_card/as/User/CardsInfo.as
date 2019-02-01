package com.sanguo.game.server.connectlogic.common.message.User
{
	import com.sanguo.game.server.ServerManager;
	import laya.utils.Byte;
	public class CardsInfo
	{
		public static const PROTO:String = "User.CardsInfo";
		public var package_root:*;
		public  var message:*;
		public var userCards:Vector.<UserCardsCPP>;
		public function CardsInfo(root:*)
		{
			package_root = root;
			message = ServerManager.getProtoMsg(PROTO);
			userCards = new Vector.<UserCardsCPP>();
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.userCards = [];
			for(var i:int = 0;i < this.userCards.length;i++)
			{
				serializeObj.userCards.push(this.userCards[i].serialize());
			}
			return serializeObj;
		}
		public function unserialize(msgObj:*):CardsInfo
		{
			userCards = new Vector.<UserCardsCPP>();
			for(var i:int = 0;i < msgObj.userCards.length;i++)
			{
				this.userCards.push(new UserCardsCPP(package_root).unserialize(msgObj.userCards[i]));
			}
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):CardsInfo
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}