package com.sanguo.game.server.connectlogic.common.message.ProtoDynamicInfo
{
	import laya.utils.Byte;
	public class ClickOrderHelpReq
	{
		public static const PROTO:String = "ProtoDynamicInfo.ClickOrderHelpReq";
		public var package_root:*;
		public  var message:*;
		public var id:int;
		public var typeId:int;
		public function ClickOrderHelpReq(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			id = undefined;
			typeId = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.id = this.id;
			serializeObj.typeId = this.typeId;
			return serializeObj;
		}
		public function unserialize(msgObj:*):ClickOrderHelpReq
		{
			id = undefined;
			typeId = undefined;
			this.id = msgObj.id;
			this.typeId = msgObj.typeId;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):ClickOrderHelpReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}