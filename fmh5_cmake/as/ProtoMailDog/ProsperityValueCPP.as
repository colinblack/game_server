package com.sanguo.game.server.connectlogic.common.message.ProtoMailDog
{
	import laya.utils.Byte;
	public class ProsperityValueCPP
	{
		public static const PROTO:String = "ProtoMailDog.ProsperityValueCPP";
		public var package_root:*;
		public  var message:*;
		public var prosperity:int;
		public var rewardts:int;
		public function ProsperityValueCPP(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			prosperity = undefined;
			rewardts = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.prosperity = this.prosperity;
			if(this.rewardts!= undefined)
			{
				serializeObj.rewardts = this.rewardts;
			}
			return serializeObj;
		}
		public function unserialize(msgObj:*):ProsperityValueCPP
		{
			prosperity = undefined;
			rewardts = undefined;
			this.prosperity = msgObj.prosperity;
			if(msgObj.hasOwnProperty("rewardts"))
			{
				this.rewardts = msgObj.rewardts;
			}
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):ProsperityValueCPP
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}