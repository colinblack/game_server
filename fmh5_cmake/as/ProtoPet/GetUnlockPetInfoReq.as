package com.sanguo.game.server.connectlogic.common.message.ProtoPet
{
	import laya.utils.Byte;
	public class GetUnlockPetInfoReq
	{
		public static const PROTO:String = "ProtoPet.GetUnlockPetInfoReq";
		public var package_root:*;
		public  var message:*;
		public function GetUnlockPetInfoReq(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			return serializeObj;
		}
		public function unserialize(msgObj:*):GetUnlockPetInfoReq
		{
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):GetUnlockPetInfoReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}