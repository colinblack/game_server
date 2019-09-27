package com.sanguo.game.server.connectlogic.common.message.ProtoKeeper
{
	import laya.utils.Byte;
	public class KeeperTaskItem
	{
		public static const PROTO:String = "ProtoKeeper.KeeperTaskItem";
		public var package_root:*;
		public  var message:*;
		public var taskId:int;
		public var need:int;
		public function KeeperTaskItem(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			taskId = undefined;
			need = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.taskId = this.taskId;
			serializeObj.need = this.need;
			return serializeObj;
		}
		public function unserialize(msgObj:*):KeeperTaskItem
		{
			taskId = undefined;
			need = undefined;
			this.taskId = msgObj.taskId;
			this.need = msgObj.need;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):KeeperTaskItem
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}