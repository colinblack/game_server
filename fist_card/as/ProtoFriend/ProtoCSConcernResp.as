package com.sanguo.game.server.connectlogic.common.message.ProtoFriend
{
	import com.sanguo.game.server.ServerManager;
	import laya.utils.Byte;
	public class ProtoCSConcernResp
	{
		public static const PROTO:String = "ProtoFriend.ProtoCSConcernResp";
		public var package_root:*;
		public  var message:*;
		public var myuid:int;
		public var info:RecommendInfo;
		public function ProtoCSConcernResp(root:*)
		{
			package_root = root;
			message = ServerManager.getProtoMsg(PROTO);
			myuid = undefined;
			info = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.myuid = this.myuid;
			serializeObj.info = this.info.serialize();
			return serializeObj;
		}
		public function unserialize(msgObj:*):ProtoCSConcernResp
		{
			myuid = undefined;
			info = undefined;
			this.myuid = msgObj.myuid;
			this.info = new RecommendInfo(package_root).unserialize(msgObj.info);
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):ProtoCSConcernResp
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}