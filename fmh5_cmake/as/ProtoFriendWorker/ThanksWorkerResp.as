package com.sanguo.game.server.connectlogic.common.message.ProtoFriendWorker
{
	import laya.utils.Byte;
	public class ThanksWorkerResp
	{
		public static const PROTO:String = "ProtoFriendWorker.ThanksWorkerResp";
		public var package_root:*;
		public  var message:*;
		public var friendworker:FriendWorkerCPP;
		public function ThanksWorkerResp(root:*)
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
		public function unserialize(msgObj:*):ThanksWorkerResp
		{
			friendworker = undefined;
			this.friendworker = new FriendWorkerCPP(package_root).unserialize(msgObj.friendworker);
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):ThanksWorkerResp
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}