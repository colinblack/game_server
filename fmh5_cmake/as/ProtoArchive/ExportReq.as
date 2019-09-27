package com.sanguo.game.server.connectlogic.common.message.ProtoArchive
{
	import laya.utils.Byte;
	public class ExportReq
	{
		public static const PROTO:String = "ProtoArchive.ExportReq";
		public var package_root:*;
		public  var message:*;
		public var uid:int;
		public function ExportReq(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			uid = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.uid = this.uid;
			return serializeObj;
		}
		public function unserialize(msgObj:*):ExportReq
		{
			uid = undefined;
			this.uid = msgObj.uid;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):ExportReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}