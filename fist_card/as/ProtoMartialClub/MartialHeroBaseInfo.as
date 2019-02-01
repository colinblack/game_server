package com.sanguo.game.server.connectlogic.common.message.ProtoMartialClub
{
	import com.sanguo.game.server.ServerManager;
	import laya.utils.Byte;
	public class MartialHeroBaseInfo
	{
		public static const PROTO:String = "ProtoMartialClub.MartialHeroBaseInfo";
		public var package_root:*;
		public  var message:*;
		public var heroid:int;
		public var slot:int;
		public var battlePower:int;
		public var coins:int;
		public var startTs:int;
		public function MartialHeroBaseInfo(root:*)
		{
			package_root = root;
			message = ServerManager.getProtoMsg(PROTO);
			heroid = undefined;
			slot = undefined;
			battlePower = undefined;
			coins = undefined;
			startTs = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			if(this.heroid!= undefined)
			{
				serializeObj.heroid = this.heroid;
			}
			if(this.slot!= undefined)
			{
				serializeObj.slot = this.slot;
			}
			if(this.battlePower!= undefined)
			{
				serializeObj.battlePower = this.battlePower;
			}
			if(this.coins!= undefined)
			{
				serializeObj.coins = this.coins;
			}
			if(this.startTs!= undefined)
			{
				serializeObj.startTs = this.startTs;
			}
			return serializeObj;
		}
		public function unserialize(msgObj:*):MartialHeroBaseInfo
		{
			heroid = undefined;
			slot = undefined;
			battlePower = undefined;
			coins = undefined;
			startTs = undefined;
			if(msgObj.hasOwnProperty("heroid"))
			{
				this.heroid = msgObj.heroid;
			}
			if(msgObj.hasOwnProperty("slot"))
			{
				this.slot = msgObj.slot;
			}
			if(msgObj.hasOwnProperty("battlePower"))
			{
				this.battlePower = msgObj.battlePower;
			}
			if(msgObj.hasOwnProperty("coins"))
			{
				this.coins = msgObj.coins;
			}
			if(msgObj.hasOwnProperty("startTs"))
			{
				this.startTs = msgObj.startTs;
			}
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):MartialHeroBaseInfo
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}