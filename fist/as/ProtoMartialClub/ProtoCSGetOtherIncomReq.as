package com.sanguo.game.server.connectlogic.common.message.ProtoMartialClub
{
	import com.sanguo.game.server.ServerManager;
	import laya.utils.Byte;
	public class ProtoCSGetOtherIncomReq
	{
		public static const PROTO:String = "ProtoMartialClub.ProtoCSGetOtherIncomReq";
		public var package_root:*;
		public  var message:*;
		public var myUid:int;
		public var othUid:int;
		public var heroId:int;
		public var slot:int;
		public function ProtoCSGetOtherIncomReq(root:*)
		{
			package_root = root;
			message = ServerManager.getProtoMsg(PROTO);
			myUid = undefined;
			othUid = undefined;
			heroId = undefined;
			slot = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.myUid = this.myUid;
			serializeObj.othUid = this.othUid;
			serializeObj.heroId = this.heroId;
			serializeObj.slot = this.slot;
			return serializeObj;
		}
		public function unserialize(msgObj:*):ProtoCSGetOtherIncomReq
		{
			myUid = undefined;
			othUid = undefined;
			heroId = undefined;
			slot = undefined;
			this.myUid = msgObj.myUid;
			this.othUid = msgObj.othUid;
			this.heroId = msgObj.heroId;
			this.slot = msgObj.slot;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):ProtoCSGetOtherIncomReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}