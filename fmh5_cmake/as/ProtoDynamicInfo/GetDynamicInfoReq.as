package com.sanguo.game.server.connectlogic.common.message.ProtoDynamicInfo
{
	import laya.utils.Byte;
	public class GetDynamicInfoReq
	{
		public static const PROTO:String = "ProtoDynamicInfo.GetDynamicInfoReq";
		public var package_root:*;
		public  var message:*;
		public function GetDynamicInfoReq(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			return serializeObj;
		}
		public function unserialize(msgObj:*):GetDynamicInfoReq
		{
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):GetDynamicInfoReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}