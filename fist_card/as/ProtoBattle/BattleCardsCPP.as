package com.sanguo.game.server.connectlogic.common.message.ProtoBattle
{
	import com.sanguo.game.server.ServerManager;
	import laya.utils.Byte;
	public class BattleCardsCPP
	{
		public static const PROTO:String = "ProtoBattle.BattleCardsCPP";
		public var package_root:*;
		public  var message:*;
		public var bag:Vector.<UserCardsCPP>;
		public var hand:Vector.<UserCardsCPP>;
		public function BattleCardsCPP(root:*)
		{
			package_root = root;
			message = ServerManager.getProtoMsg(PROTO);
			bag = new Vector.<UserCardsCPP>();
			hand = new Vector.<UserCardsCPP>();
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.bag = [];
			for(var i:int = 0;i < this.bag.length;i++)
			{
				serializeObj.bag.push(this.bag[i].serialize());
			}
			serializeObj.hand = [];
			for(var i:int = 0;i < this.hand.length;i++)
			{
				serializeObj.hand.push(this.hand[i].serialize());
			}
			return serializeObj;
		}
		public function unserialize(msgObj:*):BattleCardsCPP
		{
			bag = new Vector.<UserCardsCPP>();
			hand = new Vector.<UserCardsCPP>();
			for(var i:int = 0;i < msgObj.bag.length;i++)
			{
				this.bag.push(new UserCardsCPP(package_root).unserialize(msgObj.bag[i]));
			}
			for(var i:int = 0;i < msgObj.hand.length;i++)
			{
				this.hand.push(new UserCardsCPP(package_root).unserialize(msgObj.hand[i]));
			}
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):BattleCardsCPP
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}