package com.sanguo.game.server.connectlogic.common.message.ProtoFriendlyTree
{
	import laya.utils.Byte;
	public class RewardFriendlyTreeResp
	{
		public static const PROTO:String = "ProtoFriendlyTree.RewardFriendlyTreeResp";
		public var package_root:*;
		public  var message:*;
		public var basictreeinfo:Vector.<FriendlyTreeBasicCPP>;
		public var statustreeinfo:FriendlyTreeStatusCPP;
		public var friendlyValue:int;
		public function RewardFriendlyTreeResp(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			basictreeinfo = new Vector.<FriendlyTreeBasicCPP>();
			statustreeinfo = undefined;
			friendlyValue = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.basictreeinfo = [];
			for(var i:int = 0;i < this.basictreeinfo.length;i++)
			{
				serializeObj.basictreeinfo.push(this.basictreeinfo[i].serialize());
			}
			serializeObj.statustreeinfo = this.statustreeinfo.serialize();
			serializeObj.friendlyValue = this.friendlyValue;
			return serializeObj;
		}
		public function unserialize(msgObj:*):RewardFriendlyTreeResp
		{
			basictreeinfo = new Vector.<FriendlyTreeBasicCPP>();
			statustreeinfo = undefined;
			friendlyValue = undefined;
			for(var i:int = 0;i < msgObj.basictreeinfo.length;i++)
			{
				this.basictreeinfo.push(new FriendlyTreeBasicCPP(package_root).unserialize(msgObj.basictreeinfo[i]));
			}
			this.statustreeinfo = new FriendlyTreeStatusCPP(package_root).unserialize(msgObj.statustreeinfo);
			this.friendlyValue = msgObj.friendlyValue;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):RewardFriendlyTreeResp
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}