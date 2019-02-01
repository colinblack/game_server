package com.sanguo.game.server.connectlogic.common.message.ProtoCards
{
	import com.sanguo.game.server.ServerManager;
	import laya.utils.Byte;
	public class CardsAllChangeCPP
	{
		public static const PROTO:String = "ProtoCards.CardsAllChangeCPP";
		public var package_root:*;
		public  var message:*;
		public var cards:Vector.<UserCardsCPP>;
		public function CardsAllChangeCPP(root:*)
		{
			package_root = root;
			message = ServerManager.getProtoMsg(PROTO);
			cards = new Vector.<UserCardsCPP>();
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.cards = [];
			for(var i:int = 0;i < this.cards.length;i++)
			{
				serializeObj.cards.push(this.cards[i].serialize());
			}
			return serializeObj;
		}
		public function unserialize(msgObj:*):CardsAllChangeCPP
		{
			cards = new Vector.<UserCardsCPP>();
			for(var i:int = 0;i < msgObj.cards.length;i++)
			{
				this.cards.push(new UserCardsCPP(package_root).unserialize(msgObj.cards[i]));
			}
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):CardsAllChangeCPP
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}