package com.sanguo.game.server.connectlogic.common.message.ProtoPet
{
	import laya.utils.Byte;
	public class UnlockPetReq
	{
		public static const PROTO:String = "ProtoPet.UnlockPetReq";
		public var package_root:*;
		public  var message:*;
		public var petid:int;
		public function UnlockPetReq(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			petid = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.petid = this.petid;
			return serializeObj;
		}
		public function unserialize(msgObj:*):UnlockPetReq
		{
			petid = undefined;
			this.petid = msgObj.petid;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):UnlockPetReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}