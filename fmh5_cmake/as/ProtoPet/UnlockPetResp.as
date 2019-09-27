package com.sanguo.game.server.connectlogic.common.message.ProtoPet
{
	import laya.utils.Byte;
	public class UnlockPetResp
	{
		public static const PROTO:String = "ProtoPet.UnlockPetResp";
		public var package_root:*;
		public  var message:*;
		public var pet:UnlockPetCPP;
		public var common:CommonItemsCPP;
		public function UnlockPetResp(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			pet = undefined;
			common = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.pet = this.pet.serialize();
			serializeObj.common = this.common.serialize();
			return serializeObj;
		}
		public function unserialize(msgObj:*):UnlockPetResp
		{
			pet = undefined;
			common = undefined;
			this.pet = new UnlockPetCPP(package_root).unserialize(msgObj.pet);
			this.common = new CommonItemsCPP(package_root).unserialize(msgObj.common);
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):UnlockPetResp
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}