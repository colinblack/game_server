package com.sanguo.game.server.connectlogic.common.message.ProtoVIP
{
	import laya.utils.Byte;
	public class VIPShelfUnLockReq
	{
		public static const PROTO:String = "ProtoVIP.VIPShelfUnLockReq";
		public var package_root:*;
		public  var message:*;
		public function VIPShelfUnLockReq(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			return serializeObj;
		}
		public function unserialize(msgObj:*):VIPShelfUnLockReq
		{
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):VIPShelfUnLockReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}