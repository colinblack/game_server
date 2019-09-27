package com.sanguo.game.server.connectlogic.common.message.ProtoRandomBox
{
	import laya.utils.Byte;
	public class OpenBoxReq
	{
		public static const PROTO:String = "ProtoRandomBox.OpenBoxReq";
		public var package_root:*;
		public  var message:*;
		public function OpenBoxReq(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			return serializeObj;
		}
		public function unserialize(msgObj:*):OpenBoxReq
		{
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):OpenBoxReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}