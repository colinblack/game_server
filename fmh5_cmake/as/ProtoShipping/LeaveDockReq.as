package com.sanguo.game.server.connectlogic.common.message.ProtoShipping
{
	import laya.utils.Byte;
	public class LeaveDockReq
	{
		public static const PROTO:String = "ProtoShipping.LeaveDockReq";
		public var package_root:*;
		public  var message:*;
		public function LeaveDockReq(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			return serializeObj;
		}
		public function unserialize(msgObj:*):LeaveDockReq
		{
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):LeaveDockReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}