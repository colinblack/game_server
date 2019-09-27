package com.sanguo.game.server.connectlogic.common.message.ProtoFriend
{
	import laya.utils.Byte;
	public class CSCancelConcernResp
	{
		public static const PROTO:String = "ProtoFriend.CSCancelConcernResp";
		public var package_root:*;
		public  var message:*;
		public var myuid:int;
		public var resp:CancelConcernResp;
		public function CSCancelConcernResp(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			myuid = undefined;
			resp = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.myuid = this.myuid;
			serializeObj.resp = this.resp.serialize();
			return serializeObj;
		}
		public function unserialize(msgObj:*):CSCancelConcernResp
		{
			myuid = undefined;
			resp = undefined;
			this.myuid = msgObj.myuid;
			this.resp = new CancelConcernResp(package_root).unserialize(msgObj.resp);
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):CSCancelConcernResp
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}