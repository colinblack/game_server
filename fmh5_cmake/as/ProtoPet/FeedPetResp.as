package com.sanguo.game.server.connectlogic.common.message.ProtoPet
{
	import laya.utils.Byte;
	public class FeedPetResp
	{
		public static const PROTO:String = "ProtoPet.FeedPetResp";
		public var package_root:*;
		public  var message:*;
		public var pet:UnlockPetCPP;
		public var common:CommonItemsCPP;
		public var reward:CommonItemsCPP;
		public function FeedPetResp(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			pet = undefined;
			common = undefined;
			reward = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.pet = this.pet.serialize();
			serializeObj.common = this.common.serialize();
			if(this.reward!= undefined)
			{
				serializeObj.reward = this.reward.serialize();
			}
			return serializeObj;
		}
		public function unserialize(msgObj:*):FeedPetResp
		{
			pet = undefined;
			common = undefined;
			reward = undefined;
			this.pet = new UnlockPetCPP(package_root).unserialize(msgObj.pet);
			this.common = new CommonItemsCPP(package_root).unserialize(msgObj.common);
			if(msgObj.hasOwnProperty("reward"))
			{
				this.reward = new CommonItemsCPP(package_root).unserialize(msgObj.reward);
			}
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):FeedPetResp
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}