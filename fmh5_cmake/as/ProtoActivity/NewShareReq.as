package com.sanguo.game.server.connectlogic.common.message.ProtoActivity
{
	import laya.utils.Byte;
	public class NewShareReq
	{
		public static const PROTO:String = "ProtoActivity.NewShareReq";
		public var package_root:*;
		public  var message:*;
		public function NewShareReq(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			return serializeObj;
		}
		public function unserialize(msgObj:*):NewShareReq
		{
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):NewShareReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}