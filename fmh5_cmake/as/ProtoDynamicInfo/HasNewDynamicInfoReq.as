package com.sanguo.game.server.connectlogic.common.message.ProtoDynamicInfo
{
	import laya.utils.Byte;
	public class HasNewDynamicInfoReq
	{
		public static const PROTO:String = "ProtoDynamicInfo.HasNewDynamicInfoReq";
		public var package_root:*;
		public  var message:*;
		public function HasNewDynamicInfoReq(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			return serializeObj;
		}
		public function unserialize(msgObj:*):HasNewDynamicInfoReq
		{
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):HasNewDynamicInfoReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}