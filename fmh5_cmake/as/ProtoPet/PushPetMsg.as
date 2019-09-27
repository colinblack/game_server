package com.sanguo.game.server.connectlogic.common.message.ProtoPet
{
	import laya.utils.Byte;
	public class PushPetMsg
	{
		public static const PROTO:String = "ProtoPet.PushPetMsg";
		public var package_root:*;
		public  var message:*;
		public var pet:UnlockPetCPP;
		public function PushPetMsg(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			pet = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.pet = this.pet.serialize();
			return serializeObj;
		}
		public function unserialize(msgObj:*):PushPetMsg
		{
			pet = undefined;
			this.pet = new UnlockPetCPP(package_root).unserialize(msgObj.pet);
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):PushPetMsg
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}