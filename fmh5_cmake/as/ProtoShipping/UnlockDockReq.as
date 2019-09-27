package com.sanguo.game.server.connectlogic.common.message.ProtoShipping
{
	import laya.utils.Byte;
	public class UnlockDockReq
	{
		public static const PROTO:String = "ProtoShipping.UnlockDockReq";
		public var package_root:*;
		public  var message:*;
		public function UnlockDockReq(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			return serializeObj;
		}
		public function unserialize(msgObj:*):UnlockDockReq
		{
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):UnlockDockReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}