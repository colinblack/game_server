package com.sanguo.game.server.connectlogic.common.message.ProtoFriend
{
	import com.sanguo.game.server.ServerManager;
	import laya.utils.Byte;
	public class ProtoCSConcernReq
	{
		public static const PROTO:String = "ProtoFriend.ProtoCSConcernReq";
		public var package_root:*;
		public  var message:*;
		public var myuid:int;
		public var othuid:int;
		public function ProtoCSConcernReq(root:*)
		{
			package_root = root;
			message = ServerManager.getProtoMsg(PROTO);
			myuid = undefined;
			othuid = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.myuid = this.myuid;
			serializeObj.othuid = this.othuid;
			return serializeObj;
		}
		public function unserialize(msgObj:*):ProtoCSConcernReq
		{
			myuid = undefined;
			othuid = undefined;
			this.myuid = msgObj.myuid;
			this.othuid = msgObj.othuid;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):ProtoCSConcernReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}