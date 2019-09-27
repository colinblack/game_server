package com.sanguo.game.server.connectlogic.common.message.ProtoFriendWorker
{
	import laya.utils.Byte;
	public class SelectWorkerReq
	{
		public static const PROTO:String = "ProtoFriendWorker.SelectWorkerReq";
		public var package_root:*;
		public  var message:*;
		public var workerUid:int;
		public var pos:int;
		public function SelectWorkerReq(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			workerUid = undefined;
			pos = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.workerUid = this.workerUid;
			serializeObj.pos = this.pos;
			return serializeObj;
		}
		public function unserialize(msgObj:*):SelectWorkerReq
		{
			workerUid = undefined;
			pos = undefined;
			this.workerUid = msgObj.workerUid;
			this.pos = msgObj.pos;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):SelectWorkerReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}