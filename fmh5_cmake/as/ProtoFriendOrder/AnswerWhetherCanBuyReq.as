package com.sanguo.game.server.connectlogic.common.message.ProtoFriendOrder
{
	import laya.utils.Byte;
	public class AnswerWhetherCanBuyReq
	{
		public static const PROTO:String = "ProtoFriendOrder.AnswerWhetherCanBuyReq";
		public var package_root:*;
		public  var message:*;
		public var result:int;
		public var myuid:int;
		public var myindex:int;
		public var sourceId:int;
		public var senderUid:int;
		public function AnswerWhetherCanBuyReq(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			result = undefined;
			myuid = undefined;
			myindex = undefined;
			sourceId = undefined;
			senderUid = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.result = this.result;
			serializeObj.myuid = this.myuid;
			serializeObj.myindex = this.myindex;
			serializeObj.sourceId = this.sourceId;
			if(this.senderUid!= undefined)
			{
				serializeObj.senderUid = this.senderUid;
			}
			return serializeObj;
		}
		public function unserialize(msgObj:*):AnswerWhetherCanBuyReq
		{
			result = undefined;
			myuid = undefined;
			myindex = undefined;
			sourceId = undefined;
			senderUid = undefined;
			this.result = msgObj.result;
			this.myuid = msgObj.myuid;
			this.myindex = msgObj.myindex;
			this.sourceId = msgObj.sourceId;
			if(msgObj.hasOwnProperty("senderUid"))
			{
				this.senderUid = msgObj.senderUid;
			}
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):AnswerWhetherCanBuyReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}