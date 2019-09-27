package com.sanguo.game.server.connectlogic.common.message.ProtoShipping
{
	import laya.utils.Byte;
	public class UnveilDockReq
	{
		public static const PROTO:String = "ProtoShipping.UnveilDockReq";
		public var package_root:*;
		public  var message:*;
		public function UnveilDockReq(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			return serializeObj;
		}
		public function unserialize(msgObj:*):UnveilDockReq
		{
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):UnveilDockReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}