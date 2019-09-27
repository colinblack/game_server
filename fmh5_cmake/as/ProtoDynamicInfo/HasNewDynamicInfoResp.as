package com.sanguo.game.server.connectlogic.common.message.ProtoDynamicInfo
{
	import laya.utils.Byte;
	public class HasNewDynamicInfoResp
	{
		public static const PROTO:String = "ProtoDynamicInfo.HasNewDynamicInfoResp";
		public var package_root:*;
		public  var message:*;
		public var HasNewDy:Boolean;
		public function HasNewDynamicInfoResp(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			HasNewDy = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.HasNewDy = this.HasNewDy;
			return serializeObj;
		}
		public function unserialize(msgObj:*):HasNewDynamicInfoResp
		{
			HasNewDy = undefined;
			this.HasNewDy = msgObj.HasNewDy;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):HasNewDynamicInfoResp
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}