package com.sanguo.game.server.connectlogic.common.message.ProtoTask
{
	import laya.utils.Byte;
	public class PushComplteTask
	{
		public static const PROTO:String = "ProtoTask.PushComplteTask";
		public var package_root:*;
		public  var message:*;
		public var task:TaskCPP;
		public function PushComplteTask(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			task = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.task = this.task.serialize();
			return serializeObj;
		}
		public function unserialize(msgObj:*):PushComplteTask
		{
			task = undefined;
			this.task = new TaskCPP(package_root).unserialize(msgObj.task);
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):PushComplteTask
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}