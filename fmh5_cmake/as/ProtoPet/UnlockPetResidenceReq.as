package com.sanguo.game.server.connectlogic.common.message.ProtoPet
{
	import laya.utils.Byte;
	public class UnlockPetResidenceReq
	{
		public static const PROTO:String = "ProtoPet.UnlockPetResidenceReq";
		public var package_root:*;
		public  var message:*;
		public function UnlockPetResidenceReq(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			return serializeObj;
		}
		public function unserialize(msgObj:*):UnlockPetResidenceReq
		{
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):UnlockPetResidenceReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}