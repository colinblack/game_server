package com.sanguo.game.server.connectlogic.common.message.ProtoDynamicInfo
{
	import laya.utils.Byte;
	public class DeleteDynamicInfoReq
	{
		public static const PROTO:String = "ProtoDynamicInfo.DeleteDynamicInfoReq";
		public var package_root:*;
		public  var message:*;
		public var id:int;
		public function DeleteDynamicInfoReq(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			id = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.id = this.id;
			return serializeObj;
		}
		public function unserialize(msgObj:*):DeleteDynamicInfoReq
		{
			id = undefined;
			this.id = msgObj.id;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):DeleteDynamicInfoReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}