package com.sanguo.game.server.connectlogic.common.message.ProtoTask
{
	import laya.utils.Byte;
	public class GetTaskReq
	{
		public static const PROTO:String = "ProtoTask.GetTaskReq";
		public var package_root:*;
		public  var message:*;
		public function GetTaskReq(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			return serializeObj;
		}
		public function unserialize(msgObj:*):GetTaskReq
		{
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):GetTaskReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}