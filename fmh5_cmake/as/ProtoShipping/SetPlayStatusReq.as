package com.sanguo.game.server.connectlogic.common.message.ProtoShipping
{
	import laya.utils.Byte;
	public class SetPlayStatusReq
	{
		public static const PROTO:String = "ProtoShipping.SetPlayStatusReq";
		public var package_root:*;
		public  var message:*;
		public function SetPlayStatusReq(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			return serializeObj;
		}
		public function unserialize(msgObj:*):SetPlayStatusReq
		{
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):SetPlayStatusReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}