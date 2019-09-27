package com.sanguo.game.server.connectlogic.common.message.ProtoFriendWorker
{
	import laya.utils.Byte;
	public class SelectWorkerResp
	{
		public static const PROTO:String = "ProtoFriendWorker.SelectWorkerResp";
		public var package_root:*;
		public  var message:*;
		public var friendworker:FriendWorkerCPP;
		public function SelectWorkerResp(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			friendworker = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.friendworker = this.friendworker.serialize();
			return serializeObj;
		}
		public function unserialize(msgObj:*):SelectWorkerResp
		{
			friendworker = undefined;
			this.friendworker = new FriendWorkerCPP(package_root).unserialize(msgObj.friendworker);
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):SelectWorkerResp
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}