package com.sanguo.game.server.connectlogic.common.message.ProtoArchive
{
	import laya.utils.Byte;
	public class ImportReq
	{
		public static const PROTO:String = "ProtoArchive.ImportReq";
		public var package_root:*;
		public  var message:*;
		public var uid:int;
		public var data:UserData;
		public function ImportReq(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			uid = undefined;
			data = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.uid = this.uid;
			serializeObj.data = this.data.serialize();
			return serializeObj;
		}
		public function unserialize(msgObj:*):ImportReq
		{
			uid = undefined;
			data = undefined;
			this.uid = msgObj.uid;
			this.data = new UserData(package_root).unserialize(msgObj.data);
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):ImportReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}